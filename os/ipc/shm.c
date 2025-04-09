#include "include/types.h"
#include "include/sched.h"
#include "include/mm.h"
#include "include/string.h"

struct shm {
    char *name;
    unsigned long page;         // 固定分配一页为共享内存

    struct shm *next;
};

struct shm *shm_head;
struct shm *shm_tail;

/**
 * @brief 创建共享内存
 * @param name 共享内存名字
 */
int do_shm(char *name) {
    struct shm *shm = NULL;
    unsigned long va = 0x4000000;       // 固定虚拟地址

    for (struct shm *s = shm_head; s; s = s->next) {
        if (strcmp(s->name, name) == 0) {
            shm = s;
            break;
        }
    }

    if (!shm) {
        shm = malloc(sizeof(struct shm));
        
        int len = strlen(name);
        shm->name = malloc(len + 1);
        memcpy(shm->name, name, len);
        shm->name[len] = '\0';
        shm->page = alloc_page();
        shm->next = NULL;
        
        if (shm_head == NULL) {
            shm_head = shm;
            shm_tail = shm;
        } else {
            shm_tail->next = shm;
            shm_tail = shm;
        }
    }

    map_range(current->pml4, va, shm->page, 0x4, 1);

    return va;
}