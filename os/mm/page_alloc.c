#include "include/mm.h"

unsigned long alloc_page(void) {
    unsigned long addr;

    for (int i = KERNEL_PAGE_NUM; i < mem_size / PAGE_SIZE; i++)
        if (pages[i] == 0) {
            addr = i * PAGE_SIZE;
            pages[i] = 1;
            break;
        }

    return addr;
}

void free_page(unsigned long addr) {
    int index = addr / PAGE_SIZE;
    pages[index] = 0;
}