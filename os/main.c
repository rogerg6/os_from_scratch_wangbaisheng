#include "include/mm.h"
#include "include/sched.h"
#include "include/tss.h"
#include "include/interrupt.h"
#include "include/syscall.h"
#include "include/vesa.h"

int main(void) {
    print('M');
    print('\n');
    mm_init();

    syscall_init();
    vesa_init();

    interrupt_init();

    sched_init();
    tss_init();

    // enable timer
    init_8254();

    // unsigned long *x = VA(200 * 1024 * 1024);
    // *x = 5;
    // print(*x);

    /* 设置cr3指向进程页表 */
    __asm__("mov %0, %%cr3" : :"r"(current->pml4));

    // enable interrupt
    __asm__("sti");

    /* 跳转到用户空间 */
    __asm__(
        "mov %0, %%rsp\n\t"         //指向app1的内核栈顶
        "jmp ret_from_kernel"
        :
        : "m"(current->rsp0)
    );
}