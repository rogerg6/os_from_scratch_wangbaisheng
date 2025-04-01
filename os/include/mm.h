#include "types.h"
#include "print.h"
#include "string.h"

#define E820MAX 32
#define PAGE_SIZE (4 * 1024)
#define MAX_PAGES (1024 * 1024)             // 总的物理页 4G = 1M * 4K
#define KERNEL_PAGE_NUM (16 * 1024)         // 内核使用的物理页数 64M = 16 * 1024 * 4K

#define TASK0_PML4 0x30000                  // 根页表物理地址
#define VA(pa)  ((void*)((unsigned long)(pa) + 0xffff888000000000))   

struct e820entry {
    uint64_t addr;
    uint64_t size;
    uint32_t type;
} __attribute__((packed));

struct e820map {
    uint32_t nr_entry;
    struct e820entry map[E820MAX];
};

extern unsigned long mem_size;
extern uint8_t pages[MAX_PAGES];
unsigned long alloc_page(void);
void free_page(unsigned long addr);

void mm_init(void);