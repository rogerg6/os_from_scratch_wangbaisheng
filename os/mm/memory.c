#include "include/mm.h"

unsigned long mem_size = 0;         // 总的物理内存大小
uint8_t pages[MAX_PAGES];           // 页状态 0-free, 1-used

void mm_init(void) {
    struct e820map *e820 = (struct e820map*)0x13000;

    memset(pages, 0, MAX_PAGES);

    // 标记kernel所用的页 为已使用状态
    for (int i = 0; i < KERNEL_PAGE_NUM; i++)
        pages[i] = 1;

    for (int i = 0; i < e820->nr_entry; i++) {
        unsigned long tmp = e820->map[i].addr + e820->map[i].size;
        if (tmp > mem_size)
            mem_size = tmp;
    }

    print(mem_size);
}