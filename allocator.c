#include <stdio.h>
#include <stddef.h> // for size_t

// define a memory pool
#define MEMORY_POOL_SIZE 1024    // 1kb pool
static unsigned char memory_pool[MEMORY_POOL_SIZE];
static size_t pool_offset = 0; // where the next malloc will come from

// defining a block header to store block metadata
// type of a linked list
typedef struct block_header {
    size_t size;
    int free;
    struct block_header* next;
}


/**
 * @brief Hands out memory sequentially from a fixed buffer
 * 
 * @param size the size of the memory to be allocated
 */
void* smolalloc(size_t size) {
    if (pool_offset + size > MEMORY_POOL_SIZE) {
        printf("Cant allocate %d bytes! Out of memory!\n", size);
        // overflow condition
        return NULL;
    }
    printf("Allocating %d bytes from existing memory pool of %d\n", size, MEMORY_POOL_SIZE - pool_offset);
    void* ptr = &memory_pool[pool_offset];
    pool_offset += size;
    // move the offset by size allocated and return the pointer
    return ptr; 
}

int main() {
    int* a = (int*) smolalloc(sizeof(int)); 
    if (a) {
        *a = 42;
        printf("a = %d\n", *a);
    }

    char* b = (char*) smolalloc(10); // allocate 10 bytes to b 
    if (b) {
        for (int i = 0; i < 10; i++) {
            b[i] = 'A' + i;
        }
        b[9] = '\0';
        printf("b = %s\n", b);
    }

    int* c = (int*) smolalloc(2048);
    return 0;
}
