
#include "include/sched.h"
#include "include/mm.h"
#include "include/string.h"
#include "include/segment.h"

static struct task *task_head;
static struct task *task_tail;
struct task *current;

static void fake_task_stack(unsigned long kstack);

/**
 * @brief 创建进程
 * @param id 进程号
 * @param entry    进程虚拟加载地址
 * @param entry_pa 进程物理加载地址
 */
static void make_task(unsigned long id, unsigned long entry, 
                        unsigned long entry_pa) {

    /* 分配task */
    struct task *task = malloc(sizeof(struct task));
    task->id = id;

    /* 地址映射 */
    task->pml4 = alloc_page();
    memset(VA(task->pml4), 0, PAGE_SIZE);
    memcpy(VA(task->pml4 + 8 * 256), VA(TASK0_PML4 + 8 * 256), 8 * 256);        // 建立内核页表
    map_range(task->pml4, entry, entry_pa, 0x4, 1024);                          // 建立用户空间页表. U/S=1 4M

    /* 分配内核栈 */
    task->kstack = (unsigned long)VA(alloc_page()) + PAGE_SIZE;
    task->rsp0 = task->kstack - 8 * 5;

    /* 伪造中断现场 */
    fake_task_stack(task->kstack);

    /* 放入进程链表 */
    if (!task_head) {
        task_head = task;
        task_tail = task;
        task->prev = NULL;
        task->next = NULL;
    } else {
        // 放在链表尾部
        task_tail->next = task;
        task->prev = task_tail;
        task->next = NULL;
        task_tail = task;
    }

}

/**
 * @brief 伪造中断现场，以便启动app1
 * @param kstack: 用户进程内核栈底
 */
static void fake_task_stack(unsigned long kstack) {
    uint16_t ss = USER_DS;
    unsigned long rsp = 0x8000000;
    uint16_t cs = USER_CS;
    unsigned long rip = 0x100000;
    unsigned long rsp_tmp;

    __asm__(
        "mov %%rsp, %5\n\t"
        "mov %4, %%rsp\n\t"
        "pushq %0\n\t"
        "pushq %1\n\t"
        "pushf\n\t"
        "pushq %2\n\t"
        "pushq %3\n\t"
        "mov %5, %%rsp"
        :
        : "m"(ss), "m"(rsp), "m"(cs), "m"(rip),
          "m"(kstack), "m"(rsp_tmp)
    );
}

void sched_init(void) {
    make_task(1, 0x100000, 0xc800000);
    current = task_head;
}

void do_timer(void) {
    print('T');
}