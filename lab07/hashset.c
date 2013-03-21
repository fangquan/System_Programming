#include <stdlib.h>
#include <stdio.h>
#include "hashset.h"

#define LOAD_FACTOR 0.75f  // The ratio of elements to buckets at which a rehash should occur
#define INIT_CAP 4  // Initial number of buckets

/* A BucketNode is a node in a singly-linked list */
typedef struct BucketNode BucketNode;
struct BucketNode {
	void *value;
	BucketNode *next;
};

struct HashSet {
	unsigned int (*hashcode)(void *);  // Function to get an element's hashcode
	int (*equals)(void *, void *);  // Function to compare two elements for equality
	void *(*copy)(void *);  // Function to copy an element
	void (*delete)(void *);  // Function to delete an element

	BucketNode **buckets;  // The bucket array
	int nbuckets;  // Size of the bucket array
	int size;  // Number of elements in the set
};
/******************************
 * Creation/deletion functions
 ******************************/
/* Create a new hashset with the given element functions and return it */
HashSet *hashset_new(unsigned int (*hashcode)(void *),int (*equals)(void *, void *), void *(*copy)(void *),void (*delete)(void *)) {
        // TODO: 1. Allocate space for a HashSet struct.
        //       2. Initialize the struct, including the
	//          internal bucket array.
        HashSet *ptr_hashset = (HashSet *) malloc (sizeof(HashSet));
        ptr_hashset->hashcode = hashcode;
        ptr_hashset->equals   = equals;
        ptr_hashset->copy     = copy;
        ptr_hashset->delete   = delete;

        ptr_hashset->nbuckets = INIT_CAP;
        ptr_hashset->size = 0;
        ptr_hashset->buckets = (BucketNode **) malloc (INIT_CAP * sizeof( BucketNode *));
        for ( int i=0;i<ptr_hashset->nbuckets;i++) {
            ptr_hashset->buckets[i] = (BucketNode *) malloc (sizeof(BucketNode));
            ptr_hashset->buckets[i]->next = NULL;
            ptr_hashset->buckets[i]->value = NULL;
            // each element in this array points to the first node of a linked list
        }
	return ptr_hashset;
}

/* Delete the given hashset */
void hashset_delete(HashSet *hashset) {
        // TODO: 1. Delete all of the hashset's internal data.
	//       2. Free the struct.
    BucketNode **buckets = hashset->buckets;
    BucketNode *current,*tmp;
    for (int i=0; i < hashset->nbuckets; i++) {
            current = hashset->buckets[i];
            while (current != NULL) {
                tmp = current;
                current = current->next;
                free(tmp->value);
                free(tmp);
            }
    }
    free(buckets);
    free(hashset);
}

/******************************
 * Access/modification functions
 ******************************/

/* Add a copy of the given element to the set
 * Return 1 if the element was added successfully
 * 0 otherwise (if the element was already present)
 */
int hashset_add(HashSet *hashset, void *element) {
	// TODO: 1. Determine the bucket for the given element.
	//       2. Check if an equivalent element already exists
	//          in the corresponding bucket.
	//       3. If no equivalent element exists, create a copy of
	//          the element and store the copy in a new bucket node
	//          in the appropriate bucket.
	//       4. If the set size exceeds the load factor times
	//          the number of buckets, expand the bucket array and
	//          redistribute the existing nodes accordingly
        /*
         * If this is a brand new element, we need add it to the hashset
         */
        if (!hashset_contains(hashset, element)) {
            int bucket_number = hashset->hashcode(element) % hashset->nbuckets;
            printf( "bucketnumer: %d\n", bucket_number);
            BucketNode *current = hashset->buckets[bucket_number];
            BucketNode *newnode = (BucketNode *) malloc(sizeof(BucketNode));
            newnode->value = hashset->copy(element);
            newnode->next  = NULL;
            while ( current->next != NULL) {
                current = current->next;
            }
            current->next = newnode;
            hashset->size ++;

            BucketNode **old_buckets;

            // malloc new array, redistribute, free old buckets.
            if ( hashset->size > LOAD_FACTOR * hashset->nbuckets ) {
                 old_buckets = hashset->buckets;
                 int old_buckets_size = hashset->nbuckets;
                 int new_buckets_size = 2*hashset->nbuckets;

                 // malloc a new array and initiaze them
                 BucketNode **new_buckets = (BucketNode **) malloc (new_buckets_size * sizeof( BucketNode *));
                 for (int i=0; i<new_buckets_size;i++) {
                        new_buckets[i] = (BucketNode *) malloc (sizeof(BucketNode));
                        new_buckets[i]->next = NULL;
                        new_buckets[i]->value = NULL;
                 }

                 // redistribute each item
                 hashset->nbuckets = new_buckets_size;
                 hashset->buckets  = new_buckets;
                 void *tmp_value;
                 BucketNode *tmp_node, *current;
                 int new_bucket_number;
                 for (int i = 0; i < old_buckets_size; i++) {
                     tmp_node = old_buckets[i]->next;
                     
                     /*
                     if (tmp_node != NULL) {
                         tmp_value = tmp_node->value;
                         new_bucket_number = hashset->hashcode(tmp_value) % hashset->nbuckets;
                         hashset->buckets[new_bucket_number]->next = tmp_node;
                     }
                     */
                     
                     while (tmp_node != NULL) {
                         tmp_value = tmp_node->value;
                         new_bucket_number = hashset->hashcode(tmp_value) % hashset->nbuckets;
                         //printf("%d\n",new_bucket_number);
                         current = hashset->buckets[new_bucket_number];
                         while ( current->next != NULL) {
                                current = current->next;
                         }
                         current->next = tmp_node;
                         tmp_node = tmp_node->next;
                         current->next->next = NULL;
                     }
                 }
                 // delte old buckets.
                 // buckets is a 2d array.
                 for (int i = 0; i < old_buckets_size; i++) {
                        free(old_buckets[i]);
                     }
                 free(old_buckets);
            }
            return 1;
        }
	return 0;
}

/* Return 1 if the given element is in the set
 * 0 otherwise
 */
int hashset_contains(HashSet *hashset, void *element) {
	int bucket_number = hashset->hashcode(element) % hashset->nbuckets;
	BucketNode *current = hashset->buckets[bucket_number];
	while (current != NULL) {
		if (hashset->equals(current->value, element)) {
			return 1;
		}
		current = current->next;
	}
	return 0;
}

/* Remove the given element from the set
 * Return 1 if the element was removed successfully
 * 0 otherwise (if the element was not found)
 */
int hashset_remove(HashSet *hashset, void *element) {
	// TODO: 1. Determine the bucket for the given element.
	//       2. Check if an equivalent element already exists
	//          in the corresponding bucket.
	//       3. If an element is found, delete the hashset's copy
	//          of the element and remove the corresponding bucket node.
	if ( hashset_contains(hashset,element)) {
		int bucket_number = hashset->hashcode(element) % hashset->nbuckets;
		BucketNode *current = hashset->buckets[bucket_number];
		BucketNode *pre;	
		if (hashset->equals(current->value, element)) {
                    if (hashset->buckets[bucket_number]->next == NULL) {
                            hashset->delete(current->value);
                            current->value = NULL;
                            hashset->size --;
                            return 1;
                    }
                        hashset->buckets[bucket_number] = hashset->buckets[bucket_number]->next;
                        hashset->delete(current->value);
                        free(current);
			hashset->size --;
			return 1;
		}
		pre = current;
		current = current ->next;		
		while (current != NULL) {
			if (hashset->equals(current->value, element)) {
				pre->next = current->next;
				hashset->delete(current->value);						
				free(current);
				hashset->size --;
				return 1;
			}
			pre = current;
			current = current->next;
		}
	}
	return 0;
}

/******************************
 * Other utility functions
 ******************************/

/* Get the size of the given set */
int hashset_size(HashSet *hashset) {
	return hashset->size;
}

/* Print a representation of the hashset,
 * using the given function to print each
 * element
 */
void hashset_print(HashSet *hashset, FILE *stream, void (*print_element)(FILE *, void *)) {
	fprintf(stream, "{size=%d, buckets=%d", hashset->size, hashset->nbuckets);
	int i;
	for(i = 0; i<hashset->nbuckets; i++) {
		fprintf(stream, ", %d=[", i);
		BucketNode *bn = hashset->buckets[i];
		while(bn) {
			print_element(stream, bn->value);
			bn = bn->next;
			if(bn)
				fprintf(stream, ", ");
		}
		fprintf(stream, "]");
	}
	fprintf(stream, "}");
}










