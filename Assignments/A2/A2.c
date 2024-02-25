#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// define parameters for our arena
#define MAX_SEGREGATED_LISTS 35
#define CHUNK_SIZE 10000

// a representation for our blocks of memory
typedef struct Block {
    size_t size;
    struct Block* next;
    int free;
} Block;

// a representation for our segregated list
typedef struct {
    Block* freeList;
} SegregatedFreeList;

Block* freeList = NULL;

// initilize our segregated list with MAX_SEGREGATED_LISTS
SegregatedFreeList segregatedFreeLists[MAX_SEGREGATED_LISTS] = {0};


// helper method used to round up the size to prvent fragmentation
size_t align_size(size_t size) {
    size_t new_size = (size + sizeof(Block) - 1) - ((size + sizeof(Block) - 1) % sizeof(Block));
    return new_size;
}

// helper method used for debugging each block
void print_block_info(Block* block) {
    printf("Block at %p, size: %zu, free: %d\n", (void*)block, block->size, block->free);
}

// helper method used to return the index of the free list that can hold the size of the allocated memory 
int get_list_index(size_t size) {
    size_t adjusted_size = align_size(size);
    for (int index = 0; index < MAX_SEGREGATED_LISTS - 1; ++index) {
        if (adjusted_size <= 1) {
            return index;
        }
        adjusted_size /= 2;
    }
    return MAX_SEGREGATED_LISTS - 1;
}

// helper method to find the free block in our segregated free list
Block* find_free_block(size_t size) {
    int index = get_list_index(size);

    for (int i = index; i < MAX_SEGREGATED_LISTS; ++i) {
        if (segregatedFreeLists[i].freeList != NULL) {
            Block* block = segregatedFreeLists[i].freeList;
            segregatedFreeLists[i].freeList = block->next;
            return block;
        }
    }

    return NULL;
}

// helper method used to split the block so that we don't waste a lot of memory dur to fragmentation
void split_block(Block* block, size_t size) {
    size_t remaining_size = block->size - size - sizeof(Block);
    if (remaining_size >= sizeof(Block)) {
        Block* new_block = (Block*)((char*)block + size + sizeof(Block));
        new_block->size = remaining_size;
        new_block->next = block->next;
        block->size = size;
        block->next = new_block;
    }
}

// method used to allocate memory in our arena
void* rtos_malloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    // modify the size so the block has a perfect size in our arena
    size_t aligned_size = align_size(size);

    // find a free block that can take this allocation
    Block* block = find_free_block(aligned_size);

    if (block == NULL) {
        // if we can't find a block, use sbrk() system call to allocate a new block from the OS
        size_t block_size = aligned_size < CHUNK_SIZE ? CHUNK_SIZE : aligned_size;
        block = sbrk(block_size + sizeof(Block));
        if (block == (void*)-1) {
            return NULL;
        }

        block->size = aligned_size;
        block->free = 0;
        block->next = freeList;
        freeList = block; 

    } else {
        // if the block returend is larger than the requested size, we can split it so that we save on memory
        split_block(block, aligned_size);
    }

    // return a pointer that points at the user's data (i.e. block+1) we leave 1 as our padding
    return (void*)(block + 1);
}

// method used to free a block from a given pointer
void rtos_free(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    // retrieve pointer that points at the beginning of the block (i.e. shift by -1 to get the beginning of the block)
    Block* block_ptr = (Block*)ptr - 1;
    block_ptr->free = 1;

    // if the next block is also free, we merge them
    while (block_ptr->next && block_ptr->next->free) {
        block_ptr->size += block_ptr->next->size + sizeof(Block);
        block_ptr->next = block_ptr->next->next;
    }
}

// method used to reallocate a given block with a given size
void* rtos_realloc(void* ptr, size_t size) {
    // if pointer is null, that suggests that we need to do the regular malloc operation
    if (ptr == NULL) {
        return rtos_malloc(size);
    }

    // get the pointer that points at the beginning of the block
    Block* block = (Block*)ptr - 1;
    // get the old size 
    size_t old_size = block->size;

    // if size is 0 then we simply free that block and return
    if (size == 0) {
        rtos_free(ptr);
        return NULL;
    }

    // of the old size is bigger than the size then we can split the existing block
    if (old_size >= size) {
        split_block(block, size);
        return ptr;
    }

    // use malloc to create a new block and copy the data from the previous to new block
    void* new_ptr = rtos_malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }

    memcpy(new_ptr, ptr, old_size);
    rtos_free(ptr);

    // return the new pointer to the new reallocated block
    return new_ptr;
}

// helper method that returns the allocated size
size_t rtos_alloc_size(void* ptr) {
    if (ptr == NULL) {
        return 0;
    }

    Block* block = (Block*)ptr - 1;
    return block->size;
}

// helper method that returns whether we have a valid allocation or not
bool rtos_allocated(void* ptr) {
    if (ptr == NULL) {
        return false;
    }

    Block* block = (Block*)ptr - 1;
    return !block->free;
}

// helper method that returns total size of allocated blocks
size_t rtos_total_allocated(void) {
    size_t total = 0;

    Block* current = freeList;

    // increment total with the number of taken blocks
    while (current) {
        if (!current->free) {
            total += current->size;
        }
        current = current->next;
    }

    // loop through segregated free lists
    for (int i = 0; i < MAX_SEGREGATED_LISTS; ++i) {
        // check if the segregated free list is not empty
        if (segregatedFreeLists[i].freeList != NULL) {
            current = segregatedFreeLists[i].freeList;
            // iterate through the segregated free list
            while (current) {
                // if the block is not free, add its size to the total
                if (!current->free) {
                    total += current->size;
                }
                current = current->next;
            }
        }
    }

    // return total 
    return total;
}