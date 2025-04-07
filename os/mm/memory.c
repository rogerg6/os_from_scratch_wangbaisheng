#include "include/mm.h"
#include "include/sched.h"

unsigned long mem_size = 0;         // 总的物理内存大小
uint8_t pages[MAX_PAGES];           // 页状态 0-free, 1-used

/**
 * @param pml4_pa: 4级页表物理地址
 * @param from_va: 需要映射的起始虚拟地址
 * @param to_pa:   需要映射的起始物理地址
 * @param us:      访问权限
 * @param npage:   映射的页数
 */
void map_range(unsigned long pml4_pa, unsigned long from_va, unsigned long to_pa, char us, long npage) {
    long n = 0;

    while (n < npage) {
        // pml4
        unsigned long *page_va = VA(pml4_pa);                       // 获取页表虚拟地址
        short index = (from_va >> 39) & 0x1ff;                      // 计算页表索引

        unsigned long entry = *(page_va + index);
        if (!(entry & 0x1)) {                                       // 判断页表项是否存在
            *(page_va + index) = alloc_page() | 0x3 |  us;          // 不存在则分配页面，同时填充页表项
            entry = *(page_va + index);
        }

        // pml3
        page_va = VA(entry & 0xfffffffff000);
        index = (from_va >> 30) & 0x1ff;
        entry = *(page_va + index);
        if (!(entry & 0x1)) {
            *(page_va + index) = alloc_page() | 0x3 |  us;
            entry = *(page_va + index);
        }

        // pml2
        page_va = VA(entry & 0xfffffffff000);
        index = (from_va >> 21) & 0x1ff;
        entry = *(page_va + index);
        if (!(entry & 0x1)) {
            *(page_va + index) = alloc_page() | 0x3 |  us;
            entry = *(page_va + index);
        }

        // pml1
        page_va = VA(entry & 0xfffffffff000);
        index = (from_va >> 12) & 0x1ff;
        if (!(*(page_va + index) & 0x1))
            *(page_va + index) = (to_pa + n * PAGE_SIZE) | 0x3 |  us;

        n++;
        from_va += PAGE_SIZE;
    }
}


void mm_init(void) {
    struct e820map *e820 = (struct e820map*)0x13000;

    memset(pages, 0, MAX_PAGES);

    // 标记kernel所用的页 为已使用状态
    for (int i = 0; i < KERNEL_PAGE_NUM; i++)
        pages[i] = 1;

    // 获取内存信息
    for (int i = 0; i < e820->nr_entry; i++) {
        unsigned long tmp = e820->map[i].addr + e820->map[i].size;
        if (tmp > mem_size)
            mem_size = tmp;
    }

    print(mem_size);

    // 建立页表，映射所有的PA -> VA
    map_range(TASK0_PML4, (unsigned long)(VA(0)), 0, 0, (mem_size + PAGE_SIZE - 1) / PAGE_SIZE);
}

void do_page_fault(unsigned long addr) {
    unsigned long pa = alloc_page();
    map_range(current->pml4, addr, pa, 0x4, 1);
}
