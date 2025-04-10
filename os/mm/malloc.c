#include "include/mm.h"
#include "include/types.h"

// 桶
struct bucket_desc {
    void *freeptr;              // 指向单个块
    struct bucket_desc *next;   // 指向下一个桶
    short refcnt;
};

struct bucket_dir {
    short size;                 // 块大小
    struct bucket_desc *bdesc;
};

// 存放不同大小的块的桶链表
struct bucket_dir bucket_dir[] = {
    {32, NULL}, 
    {64, NULL}, 
    {128, NULL}, 
    {256, NULL}, 
    {512, NULL}, 
    {1024, NULL}, 
    {2048, NULL}, 
    {0, NULL}, 
};


void *malloc(int size) {
    void *va = NULL;
    struct bucket_dir *bdir = NULL;
    struct bucket_desc *bdesc = NULL;

    // 寻找能容下size的块桶
    for (bdir = bucket_dir; bdir->size != 0; bdir++)
        if (bdir->size >= size)
            break;
    if (bdir->size == 0)
        return NULL;

    // 寻找桶中空闲的块
    for (bdesc = bdir->bdesc; bdesc; bdesc = bdesc->next)
        if (bdesc->freeptr)
            break;
    
    // 无桶，分配桶
    if (bdesc == NULL) {
        bdesc = VA(alloc_page());

        bdesc->next = NULL;
        bdesc->refcnt = 0;
        bdesc->freeptr = (void*)((unsigned long)bdesc + sizeof(struct bucket_desc));

        unsigned long *p = bdesc->freeptr;
        int i;
        while (++i < (PAGE_SIZE - sizeof(struct bucket_desc)) / bdir->size) {
            *p = (unsigned long)p + bdir->size;
            p = (unsigned long*)((unsigned long)p + bdir->size);
        }
        *p = 0;

        // 新桶插入桶链表头
        bdesc->next = bdir->bdesc;
        bdir->bdesc = bdesc;
    }

    va = bdesc->freeptr;
    bdesc->freeptr = (void*)(*((unsigned long*)va));
    bdesc->refcnt++;

    return va;
}

void free(void *obj) {
    unsigned long page = (unsigned long)obj & ~0xfff;
    struct bucket_dir *bdir = bucket_dir;
    struct bucket_desc *bdesc = NULL;

    for (; bdir->size != 0; bdir++) {
        bdesc = bdir->bdesc;
        for (; bdesc; bdesc = bdesc->next) {
            if ((unsigned long)bdesc == page) {
                // 把obj放在桶链表头
                *((unsigned long*)obj) = (unsigned long)bdesc->freeptr;
                bdesc->freeptr = obj;
                bdesc->refcnt--;
                goto free_page;
            }
        }
    }

free_page:
    // free bdesc
    if (bdesc && bdesc->refcnt == 0) {
        struct bucket_desc *tmp = bdir->bdesc;
        struct bucket_desc *prev = NULL;
        for (; tmp; tmp = tmp->next) {
            if ((unsigned long)tmp == (unsigned long)bdesc)
                break;
            prev = tmp;
        }

        if (!prev)
            bdir->bdesc = tmp->next;
        else 
            prev->next = tmp->next;

        free_page(PA(bdesc));
    }
}