#include "salloc.h"
void *salloc(size_t size) {
    void *ret = malloc(size);
    if (ret == NULL) {
        printf("Out of memory error!\n");
        exit(1);
    }
    return ret;
}
