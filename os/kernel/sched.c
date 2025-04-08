
#include "include/sched.h"
#include "include/mm.h"
#include "include/string.h"
#include "include/segment.h"
#include "include/types.h"
#include "include/tss.h"

static struct task *task_head;
static struct task *task_tail;
struct task *current;
struct task *idle_task;

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
    task->state = TASK_RUNNING;

    /* 地址映射 */
    task->pml4 = alloc_page();
    memset(VA(task->pml4), 0, PAGE_SIZE);
    memcpy(VA(task->pml4 + 8 * 256), VA(TASK0_PML4 + 8 * 256), 8 * 256);        // 建立内核页表
    map_range(task->pml4, entry, entry_pa, 0x4, 1024);                          // 建立用户空间页表. U/S=1 4M

    /* 分配内核栈 */
    task->kstack = (unsigned long)VA(alloc_page()) + PAGE_SIZE;

    /* 伪造中断现场 */
    fake_task_stack(task->kstack);
    task->rsp0 = task->kstack - 8 * 5;
    task->rip = (unsigned long)&ret_from_kernel;

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

static void make_idle_task(void) {
    idle_task = malloc(sizeof(struct task));
    idle_task->id = 0;
    idle_task->state = TASK_RUNNING;
    idle_task->pml4 = TASK0_PML4;
    idle_task->kstack = (unsigned long)&task0_stack;
    idle_task->rsp0 = (unsigned long)&task0_stack;
    idle_task->rip = (unsigned long)&idle_task_entry;
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
    make_task(2, 0x100000, 0xd000000);
    make_idle_task();
    current = task_head;
}

void schedule(void) {
    struct task *next = NULL;

    for (struct task *t = task_head; t; t = t->next){
        if (t->state == TASK_RUNNING) {
            next = t;
            break;
        }
    }

    if (!next)
        next = idle_task;

    // 切换任务
    if (next != current) {
        __asm__(                                            
            // 保存当前任务rsp,rip
            "mov %%rsp, %0\n\t"                             
            "movq $1f, %1\n\t"                              

            // 加载下个任务rsp,rip
            "mov %2, %%rsp\n\t"                             
            "push %3\n\t"                                   
            : "=m"(current->rsp0), "=m"(current->rip)       
            : "m"(next->rsp0), "m"(next->rip)               
        );

        tss.rsp0 = (unsigned long)next->kstack;
        current = next;

        __asm__("mov %0, %%cr3" : : "a"(next->pml4));
        __asm__("ret");

        __asm__("1:");
    }
    
}

void do_timer(void) {
    // print('T');
    if (current != idle_task) {
        if (current != task_tail) {
            // 把当前任务移到队尾
            if (current->prev) 
                current->prev->next = current->next;
            current->next->prev = current->prev;

            current->prev = task_tail;
            task_tail->next = current;

            if (current == task_head)
                task_head = current->next;
            task_tail = current;

            current->next = NULL;
        }
    }

    schedule();
}