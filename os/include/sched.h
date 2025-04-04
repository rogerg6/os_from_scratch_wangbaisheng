
// 进程
struct task {
    unsigned long id;           // pid
    unsigned long rip;          // 切换任务时指令的地址
    unsigned long rsp0;         // 切换任务时内核栈顶
    unsigned long kstack;       // 内核栈底
    unsigned long pml4;         // 根页表地址

    struct task *prev;
    struct task *next;
};

extern struct task *current;



void sched_init(void);