#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "mm.h"
#include "memlib.h"
/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8
/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
/* SIZE_T_SIZE is always 8 */
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))
#define BLKSIZE 16  // Minimal size include header/footer, next_ptr/prev_ptr
#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE  (1<<12)  /*Extend heap by this amount bytes, 4096 bytes*/
#define MAX(x,y) ((x) > (y) ? x : y)
#define MIN(x,y) ((x) < (y) ? x : y)
/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size)|(alloc))
/* Read and Write a word at address p */
#define GET(p)          (*(unsigned int *) (p))
/* Casting and assigning */
#define PUT(p,val)      (*(unsigned int *) (p) = (val))
/* Read the size and allocated fields from address p*/
#define GET_SIZE(p)     (GET(p) & ~0x7)
#define GET_ALLOC(p)    (GET(p) & 0x1)
/* Given block prt bp, compute address of its header and footer*/
/* Addresses of pointers of next and prev*/
#define HDRP(bp) ((char*)(bp) - WSIZE)
#define FTRP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)
#define NEXT_FREE_PTR(bp) ((char*)(bp))
#define PREV_FREE_PTR(bp) ((char*)(bp) + WSIZE)
/* Given block ptr bp, compute address of next and previous free blocks*/
#define NEXT_FREE(bp)       ((void *)GET(NEXT_FREE_PTR(bp)))
#define PREV_FREE(bp)       ((void *)GET(PREV_FREE_PTR(bp)))
#define PUT_NEXT(bp,val)    PUT(NEXT_FREE_PTR(bp),(int) val)
#define PUT_PREV(bp,val)    PUT(PREV_FREE_PTR(bp),(int) val)
/* Given block ptr bp, computer address of next and previous blocks*/
#define NEXT_BLKP(bp)   ((char *)(bp) + GET_SIZE(((char*)(bp) - WSIZE)))
#define PREV_BLKP(bp)   ((char *)(bp) - GET_SIZE(((char*)(bp) - DSIZE)))

static char *heap_listp;
static void *free_list_rt = NULL;
static void *extend_heap(size_t);
static void *coalesce(void *bp);
static void insert_node(void *bp);
static void delete_node(void *bp);
static void place(void *bp, size_t asize);
static void *find_fit (size_t asize);
static void checkfreelist(int);
static void checkheap(int);
static void printblock(void*);
static void checkblock(void*);

/*
 * initializes the dynamic allocator
 * arguments: none
 * returns: 0, if successful
 *          -1, if an error occurs
 */
int mm_init(void) {
    if ((heap_listp = mem_sbrk(4*WSIZE)) == (void *) -1)
        return -1;
    PUT(heap_listp,0);
    PUT(heap_listp+(1*WSIZE),PACK(DSIZE,1));
    PUT(heap_listp+(2*WSIZE),PACK(DSIZE,1));
    PUT(heap_listp+(3*WSIZE),PACK(0,1));
    heap_listp += DSIZE;
    free_list_rt = NULL;
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL) {
        return -1;
    }
    //checkheap(1);
    //checkfreelist(1);
    return 0;
}

/*
 * allocates a block of memory and returns a pointer to that block
 * arguments: size: the desired block size
 * returns: a pointer to the newly-allocated block (whose size
 *          is a multiple of ALIGNMENT), or NULL if an error
 *          occurred
 */
void *mm_malloc(size_t size) {
    size_t asize;           // adjusted block size
    size_t extendsize;      // amount to extend heap if no fit
    char *bp;
    // Ignore spurious requests
    if (size <= 0) {
        return NULL;
    }
    // Adjust block size to include overhead and alignment reqs
    if (size <= DSIZE) {
        asize = 2*DSIZE;
    }
    else {
        asize = DSIZE*((size + DSIZE + (DSIZE-1))/DSIZE);
    }
    // Search the free list for a fit
    // find_fit go through the free list
    // place() (1) places the bp; (2) split that block; (3) Organize the linked list
    if ((bp = find_fit(asize)) != NULL) {
        //printf("\nFind fit\n");
        place(bp,asize);
        //checkheap(1);
        //checkfreelist(1);
        return bp;
    }
    // No fit found. Get more memory and place the block
    //printf("\nCan't find fit\n");
    extendsize = MAX(asize,CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL) {
        return NULL;
    }
    place(bp,asize);
    //checkheap(1);
    //checkfreelist(1);
    return bp;
}

/*
 * frees a block of memory, enabling it to be reused later
 * arguments: ptr: the allocated block to free
 * returns: nothing
 */
void mm_free(void *ptr) {
    //printf("\nfree %p\n",ptr);
    size_t size = GET_SIZE(HDRP(ptr));
    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    void * bp1  =  coalesce(ptr);
    insert_node(bp1);
    //checkheap(1);
    //checkfreelist(1);
}

/*
 * reallocates a memory block to update it with the given size
 * arguments: ptr: a pointer to the memory block
 *            size: the desired new block size
 * returns: a pointer to the new memory block
 */
void *mm_realloc(void *ptr, size_t size) {
    char *bp;

    /* ptr == NULL, simply call malloc */
    if (ptr == NULL) {
        bp = mm_malloc(size);
    }
    /* size == 0, simply call mm_free*/
    else if (size == 0) {
        mm_free(ptr);
    }
    else {
        size_t oldsize = GET_SIZE(HDRP(ptr));
        /*Case1, new size is less than oldsize
          Simply return the old address ptr
         */
        if ((oldsize - DSIZE) >= size) {
            bp = ptr;
            return bp;
        }
        /*Case2.1, extend to next block if it's free. Merge the current and next
          block. Compare the requested size to the merged size
         */
        if (!GET_ALLOC(HDRP(NEXT_BLKP(ptr)))) {
            size_t tmpsize = GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(NEXT_BLKP(ptr)));
            if ((tmpsize - DSIZE) >= size) {
                delete_node(NEXT_BLKP(ptr));
                PUT(HDRP(ptr), PACK(tmpsize,1));
                PUT(FTRP(ptr), PACK(tmpsize,1));
                bp = ptr;
                return bp;
            }
        }
        /*Case2.2, extend to prev block if it's free. Merge the current and prev
          block. Compare the requested size to the merged size
         */
        if (!GET_ALLOC(HDRP(PREV_BLKP(ptr)))) {
            size_t tmpsize = GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(PREV_BLKP(ptr)));
            if ((tmpsize - DSIZE) >= size) {
                delete_node(PREV_BLKP(ptr));
                bp = PREV_BLKP(ptr);// HDRP(ptr) maybe overwritten, save it here
                PUT(HDRP(PREV_BLKP(ptr)),PACK(tmpsize,1));
                PUT(FTRP(PREV_BLKP(ptr)),PACK(tmpsize,1));
                memcpy(PREV_BLKP(ptr),ptr,MIN(size,GET_SIZE(HDRP(ptr))));
                return bp;
            }
        }
        /*Case2.3, extend to prev block and next block if they're free. 
         * Merge the current, prev and next block. Compare the requested size
         * to the merged size
         */
        if (!GET_ALLOC(HDRP(PREV_BLKP(ptr))) && !GET_ALLOC(HDRP(NEXT_BLKP(ptr)))) {
                size_t tmpsize = GET_SIZE(HDRP(PREV_BLKP(ptr))) + GET_SIZE(HDRP(ptr)) + GET_SIZE(HDRP(NEXT_BLKP(ptr)));
                if ((tmpsize - DSIZE) >= size) {
                delete_node(NEXT_BLKP(ptr));
                delete_node(NEXT_BLKP(ptr));
                bp = PREV_BLKP(ptr);// HDRP(ptr) maybe overwritten, save it here
                PUT(HDRP(PREV_BLKP(ptr)), PACK(tmpsize,1));
                PUT(FTRP(NEXT_BLKP(ptr)), PACK(tmpsize,1));
                memcpy(PREV_BLKP(ptr),ptr,MIN(size,GET_SIZE(HDRP(ptr))));
                return bp;
                }
        }

        /* Case 3, requested size is very big, simply malloc new heap and memcpy*/
        else {
            bp = mm_malloc(size);
            memcpy(bp,ptr,MIN(oldsize,size));
            mm_free(ptr);
            return bp;
        }
    }
    return bp;
}

/*extend_heap always created a free block, we need to insert this node
  extending is done by calling mem_sbrk, the newly extended block will be
  treated as a free block, and inserted to the beginning of the list.
 */
static void *extend_heap(size_t words) {
    char *bp;
    size_t size;
    /* Allocate an even number of words to maintain alignment, in order to align 8 bytes */
    size = (words % 2) ? (words+1)*WSIZE : words*WSIZE;
    if ((long) (bp = mem_sbrk(size)) == -1) {
        return NULL;
    }
    /* Reinitialize free block header/footer and the epilogue header*/
    PUT(HDRP(bp),PACK(size,0));
    PUT(FTRP(bp),PACK(size,0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0,1));
    /* Coalesce if the previous blokc was free */
    /* This is a brand new node, we need to insert it somewhere */
    void * bp1  =  coalesce(bp);
    insert_node(bp1);
    return bp1;
}

// If a block coalesced, it will be deleted from the list
static void *coalesce(void *bp) {
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp)); // current block's size
    /* Case 1 */
    // Delete nothing
    if( prev_alloc && next_alloc) {
        return bp;
    }
    /* Case 2 */
    // Delete NEXT_BLKP from the list
    else if (prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        delete_node(NEXT_BLKP(bp));
        PUT(HDRP(bp), PACK(size,0));
        PUT(FTRP(bp), PACK(size,0));
    }
    /* Case 3 */
    else if (!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        delete_node(PREV_BLKP(bp));
        PUT(FTRP(bp), PACK(size,0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size,0));
        bp = PREV_BLKP(bp);
    }
    else {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
        delete_node(NEXT_BLKP(bp));
        delete_node(PREV_BLKP(bp));
        PUT(HDRP(PREV_BLKP(bp)),PACK(size,0));
        PUT(FTRP(NEXT_BLKP(bp)),PACK(size,0));
        bp = PREV_BLKP(bp);
    }
    return bp;
}

/*New free block will be inserted into the head of the freelist
  The global free_list_root will point to this block, and this block's NEXT_FREE 
  is the old root, and PREV_FREE is NULL now.  
 */
static void insert_node(void *bp){
    if (free_list_rt == NULL) {
        free_list_rt = bp;
        PUT_PREV(bp,NULL);
        PUT_NEXT(bp,NULL);
    }
    else {
        PUT_NEXT(bp,free_list_rt);
        PUT_PREV(bp,NULL);
        PUT_PREV(free_list_rt,bp);  // This is important
        free_list_rt = bp;
    }
}

/*  Delete a node during coalsece
    By modifying the PREV_FREE and NEXT_FREE address to NULL.
 */
static void delete_node(void *bp) {
     void *before = PREV_FREE(bp);
     void *after  = NEXT_FREE(bp);
     if (free_list_rt == bp) {
         free_list_rt = NULL;
     }
     // First case:
     if (before == NULL && after != NULL) {
            free_list_rt = after;
            PUT_PREV(after,NULL);
     }
     else if (before != NULL && after == NULL ) {
            PUT_NEXT(before,NULL);
     }
     else if (after == NULL && before == NULL) {
         free_list_rt = NULL;
     }
     else if (after != NULL && before != NULL){
         PUT_NEXT(before,after);
         PUT_PREV(after,before);
     }



}

/* Go through the whole free list, find block big enough to fit asize*/
static void *find_fit(size_t asize) {
    void *bp = free_list_rt;
    for (;bp != NULL;bp = NEXT_FREE(bp)) {
        if (asize <= GET_SIZE(HDRP(bp))) {
            return bp;
        }
    }
    return NULL;
}

/* Two tasks (1) Change block alloc status; (2) delete node */
static void place(void *bp, size_t asize) {
    size_t blocksize = GET_SIZE(HDRP(bp));
    delete_node(bp);

    /*Case 1, big enough to split */
    if ((blocksize - asize) >= (2*DSIZE)) {
        PUT(HDRP(bp), PACK(asize, 1));
	PUT(FTRP(bp), PACK(asize, 1));
        void *bp1 = NEXT_BLKP(bp);
	PUT(HDRP(bp1), PACK(blocksize-asize, 0));
	PUT(FTRP(bp1), PACK(blocksize-asize, 0));
        insert_node(bp1);
    }
    /*Case 2, not big enough, don't split*/
    else {
        PUT(HDRP(bp), PACK(blocksize, 1));
	PUT(FTRP(bp), PACK(blocksize, 1));
    }
}

/*Print the free block list
 For example:
 free_list_rt (0xb620b018):0xb620b018: h(4096|0) f(4096|0) 
 */
static void checkfreelist (int verbose) {
    void * bp = free_list_rt;
    if (verbose && free_list_rt != NULL) {
	printf("free_list_rt (%p):\n", free_list_rt);
    }


    for (bp = free_list_rt; bp != NULL; ) {
	if (verbose)
	    printblock(bp);
	checkblock(bp);
        bp = NEXT_FREE(bp);
    }
}

/*Print the whole heap, including alloc and free blocks
 For example:
 Heap (0xb6234010):0xb6234010: h(8|1) f(8|1) ||0xb6234018: h(4096|0) f(4096|0) ||0xb6235018: EOL
 */

static void checkheap(int verbose) {
    char *bp = heap_listp;

    if (verbose)
	printf("Heap (%p):\n", heap_listp);

    if ((GET_SIZE(HDRP(heap_listp)) != DSIZE) || !GET_ALLOC(HDRP(heap_listp)))
	printf("Bad prologue header\n");
    checkblock(heap_listp);

    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp)) {
	if (verbose)
	    printblock(bp);
	checkblock(bp);
    }

    if (verbose)
	printblock(bp);
    if ((GET_SIZE(HDRP(bp)) != 0) || !(GET_ALLOC(HDRP(bp))))
	printf("Bad epilogue header\n");
}

/* Print a single block
 Format:
 || address:h(size|alloc_sign) f(size|alloc_sign) ||
 */
static void printblock(void *bp) {
    size_t hsize, halloc, fsize, falloc;
    hsize   = GET_SIZE (HDRP(bp));
    halloc  = GET_ALLOC(HDRP(bp));
    fsize   = GET_SIZE (FTRP(bp));
    falloc  = GET_ALLOC(FTRP(bp));

    if (hsize == 0) {
	printf("%p: EOL\n", bp);
	return;
    }
    printf("%p: h(%d|%d) f(%d|%d) ||", bp, hsize, (halloc ? 1 : 0),fsize, (falloc ? 1 : 0));
}

/*
 * Check the eligibility of a specific block (1) 8 bytes alignment; (2)header, footer consistency
 */
static void checkblock(void *bp)
{
    if ((size_t)bp % 8)
	printf("Error: %p is not doubleword aligned\n", bp);
    if (GET(HDRP(bp)) != GET(FTRP(bp)))
	printf("Error: header does not match footer\n");
}

