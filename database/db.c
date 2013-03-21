#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/file.h>
#include "db.h"

typedef struct DBNode DBNode;
enum locktype {l_read,l_write};
#define lock(lt,lk) ((lt) == l_read ) ? pthread_rwlock_rdlock(lk) : pthread_rwlock_wrlock(lk)
/* Struct representing a database node */
struct DBNode {
	char *name;
	char *value;
	DBNode *lchild;
	DBNode *rchild;
        pthread_rwlock_t rwlock;
};

/* Struct representing a database */
struct Database {
	DBNode *root;
};

// Forward declarations
static DBNode *dbnode_new(char *name, char *value, DBNode *left, DBNode *right);
static void dbnode_delete(DBNode *node);
static void dbnode_rdelete(DBNode *node);
static DBNode *search(DBNode *parent, char *name, DBNode **parentpp, enum locktype lt);
static void dbnode_print(DBNode *node, FILE *file);
static void dbnode_rprint(DBNode *node, FILE *file, int level);
static void print_spaces(FILE *file, int nspaces);

/****************************************
 * Database creation/deletion functions
 ****************************************/
/* Create a database */
Database *db_new() {
	Database *db = (Database *)malloc(sizeof(Database));
	if(!db)
		return NULL;

	if(!(db->root = dbnode_new("", "", NULL, NULL))) {
		free(db);
		return NULL;
	}
	return db;
}

/* Delete a database */
void db_delete(Database *db) {
	if(db) {
		dbnode_rdelete(db->root);  // Delete all nodes in the database
		free(db);
	}
}

/* Create a database node */
static DBNode *dbnode_new(char *name, char *value, DBNode *left, DBNode *right) {
	DBNode *node = (DBNode *)malloc(sizeof(DBNode));
	if(!node)
		return NULL;
	if(!(node->name = (char *)malloc(strlen(name)+1))) {
		free(node);
		return NULL;
	}
	if(!(node->value = (char *)malloc(strlen(value)+1))) {
		free(node->name);	
		free(node);
		return NULL;
	}

	strcpy(node->name, name);
	strcpy(node->value, value);

	node->lchild = left;
	node->rchild = right;

	return node;
}

/* Delete a database node */
static void dbnode_delete(DBNode *node) {
        pthread_rwlock_unlock(&node->rwlock);
	free(node->name);
	free(node->value);
	free(node);
}

/* Recursively delete a database node and all children */
static void dbnode_rdelete(DBNode *node) {
	if(node) {
		dbnode_rdelete(node->lchild);
		dbnode_rdelete(node->rchild);
		dbnode_delete(node);
	}
}

/****************************************
 * Access/modification functions
 ****************************************/
/* Add a key-value pair to the database
 *
 * db    - The database
 * name  - The key to add
 * value - The corresponding value
 * Return 1 on success, 0 on failure
 */
int db_add(Database *db, char *name, char *value) {
	DBNode *parent;
        enum locktype lt = l_write;
        lock(lt,&db->root->rwlock);
	DBNode *target = search(db->root, name, &parent, lt);
        
	if(target) {                                
                // Name is already in database
                // return target and parent locked
                // we need to unlock them
                pthread_rwlock_unlock(&target->rwlock);
                pthread_rwlock_unlock(&parent->rwlock);
		return 0;
        }
	target = dbnode_new(name, value, NULL, NULL);
        pthread_rwlock_init(&target->rwlock,0);
	if(strcmp(name, parent->name)<0)
		parent->lchild = target;
	else
		parent->rchild = target;
        // node not found, we need to unlock the parent
        pthread_rwlock_unlock(&parent->rwlock);
	return 1;
}

/* Search for the value corresponding to a given key
 *
 * db    - The database
 * name  - The key to search for
 * value - A buffer in which to store the result
 * len   - The result buffer length
 *
 * Return 1 on success, 0 on failure
 */
int db_query(Database *db, char *name, char *value, int len) {
        enum locktype lt = l_read;
        lock(lt,&db->root->rwlock);
	DBNode *target = search(db->root, name, NULL,lt);
	if(target) {
		int tlen = strlen(target->value) + 1;
		strncpy(value, target->value, (len < tlen ? len : tlen));
                // unlock the target node
                pthread_rwlock_unlock(&target->rwlock);
		return 1;
	} else {
		return 0;
	}
}

/* Delete a key-value pair from the database
 *
 * db    - The database
 * name  - The key to delete
 *
 * Return 1 on success, 0 on failure
 */
int db_remove(Database *db, char *name) {
	DBNode *parent;
        enum locktype lt = l_write;
        lock(lt,&db->root->rwlock);
	DBNode *target = search(db->root, name, &parent,lt);

	if(!target) {  
                // Name is not in database
                // unlock the parent
                pthread_rwlock_unlock(&parent->rwlock);
		return 0;
        }
	DBNode *tleft = target->lchild;
	DBNode *tright = target->rchild;

	dbnode_delete(target);

	DBNode *successor;

	if(!tleft) {
		// If deleted node has no left child, promote right child
		successor = tright;
	} else if(!tright) {
		// If deleted node has not right child, promote left child
		successor = tleft;
	} else {
		// If deleted node has both children, find leftmost child
		// of right subtree.  This node is less than all other nodes in
		// the right subtree, and greater than all nodes in the left subtree,
		// so it can be used to replace the deleted node.

		DBNode *sp = NULL;
		successor = tright;
		while(successor->lchild) {
			sp = successor;
			successor = successor->lchild;
		}

		if(sp) {
			sp->lchild = successor->rchild;
			successor->rchild = tright;
		}

		successor->lchild = tleft;
	}

	if(strcmp(name, parent->name)<0)
		parent->lchild = successor;
	else
		parent->rchild = successor;
        pthread_rwlock_unlock(&parent->rwlock);
	return 1;
}

/* Search the tree, starting at parent, for a node whose name is
 * as specified.
 *
 * Return a pointer to the node if found, or NULL otherwise.
 *
 * If parentpp is not NULL, then it points to a location at which
 * the address of the parent of the target node is stored. 
 * If the target node is not found, the location pointed to by
 * parentpp is set to what would be the the address of the parent
 * of the target node, if it existed.
 * 
 * Assumptions: parent is not null and does not contain name
 * parent is already locked on entry
 */
static DBNode *search(DBNode *parent, char *name, DBNode **parentpp, enum locktype lt) {
	DBNode *next = parent;
	do {
                parent = next;
		if(strcmp(name, parent->name) < 0) {
                        // left child
			next = parent->lchild;
                }
		else if (strcmp(name, parent->name) > 0){
                        // right child
			next = parent->rchild;
                }
                // If we return NULL, parent still locked
                if (next && parent != next) {
                        lock(lt,&next->rwlock);
                        if (strcmp(name, next->name) != 0) {
                            pthread_rwlock_unlock(&parent->rwlock);
                        }
                }
                // if name found, this node locked and returned
	}while(next && strcmp(name, next->name));
	if(parentpp) {
		*parentpp = parent;
        }
        else {
               pthread_rwlock_unlock(&parent->rwlock);
        }
	return next;
}

/*********************************************
 * Database printing functions
 *********************************************/

/* Print contents of database to the given file */
void db_print(Database *db, FILE *file) {
        flock(fileno(file), LOCK_EX);
        // FILE * is a buffered fd, getting fd from FILE *, just use fileno
	dbnode_rprint(db->root, file, 0);
        flock(fileno(file),LOCK_UN);
}

/* Print a representation of the given node */
static void dbnode_print(DBNode *node, FILE *file) {
	if(!node)
		fprintf(file, "(null)\n");
	else if(!*(node->name))  // Root node has name ""
		fprintf(file, "(root)\n");
	else
		fprintf(file, "%s %s\n", node->name, node->value);
}

/* Recursively print the given node followed by its left and right subtrees */
static void dbnode_rprint(DBNode *node, FILE *file, int level) {
	print_spaces(file, level);
	dbnode_print(node, file);
	if(node) {
		dbnode_rprint(node->lchild, file, level+1);
		dbnode_rprint(node->rchild, file, level+1);
	}
}

/* Print the given number of spaces */
static void print_spaces(FILE *file, int nspaces) {
	while(0 < nspaces--)
		fprintf(file, " ");
}
