#include "include/segment.h"

.text
.code64

start64:
    # 64位模式
    mov $0x3f8, %dx
    mov $'L', %al
    out %al, %dx

    lgdt gdtr

    # 初始化段寄存器
    mov $KERNEL_DS, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %gs
    mov %ax, %fs
    mov %ax, %ss

    # 设置栈
    mov $task0_stack, %rsp

    # 跳到C语言 main函数
    push $main
    ret

    hlt

.align 64
gdt:
    .quad 0x0000000000000000
    .quad 0x00209a0000000000        # 64bit kernel cs
    .quad 0x0000920000000000        # 64bit kernel ds
    .quad 0x0000000000000000        # 32bit user cs
    .quad 0x0000f20000000000        # 32bit user ds
    .quad 0x0020fa0000000000        # 64bit user cs
    .fill 128, 8, 0
gdt_end:

gdtr:
    .word gdt_end - gdt
    .quad gdt           # 段基址是0，gdt地址就是gdt


// 4KB stack
.fill 4096, 1, 0
task0_stack: