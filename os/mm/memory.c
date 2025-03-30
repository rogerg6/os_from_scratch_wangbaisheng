#include "include/mm.h"
#include "include/print.h"

unsigned long mem_size = 0;

void mm_init(void) {
    struct e820map *e820 = (struct e820map*)0x13000;

    for (int i = 0; i < e820->nr_entry; i++) {
        unsigned long tmp = e820->map[i].addr + e820->map[i].size;
        if (tmp > mem_size)
            mem_size = tmp;
    }

    print(mem_size);
}