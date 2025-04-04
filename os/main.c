#include "include/mm.h"
#include "include/sched.h"
#include "include/tss.h"


int main(void) {
    __asm__(
        "mov $0x3f8, %dx\n\t"
        "mov $'M', %ax\n\t"
        "out %ax, %dx\n"
    );
    mm_init();
    sched_init();
    tss_init();

    // unsigned long *x = VA(200 * 1024 * 1024);
    // *x = 5;
    // print(*x);

    /* 设置cr3指向进程页表 */
    __asm__("mov %0, %%cr3" : :"r"(current->pml4));

    /* 跳转到用户空间 */
    __asm__(
        "mov %0, %%rsp\n\t"         //指向app1的内核栈顶
        "jmp ret_from_kernel"
        :
        : "m"(current->rsp0)
    );
}