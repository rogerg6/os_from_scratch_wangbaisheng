
enum task_state {
    TASK_RUNNING = 0,           // 运行状态
    TASK_INTERRUPTIBLE          // 可中断的睡眠状态
};

// 进程
struct task {
    enum task_state state;
    unsigned long id;           // pid
    unsigned long rip;          // 切换任务时指令的地址
    unsigned long rsp0;         // 切换任务时内核栈顶
    unsigned long kstack;       // 内核栈底
    unsigned long pml4;         // 根页表地址

    struct task *prev;
    struct task *next;
};

extern struct task *current;
extern unsigned long task0_stack;
extern unsigned long idle_task_entry;
extern unsigned long ret_from_kernel;



void sched_init(void);
void do_timer(void);