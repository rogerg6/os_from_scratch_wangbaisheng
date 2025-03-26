# 函数
# x86调用约定
#

.text
.code16

start:
    mov $stack, %sp         # 初始化栈指针
    call sum

    mov $0x3f8, %dx
    out %ax, %dx
    hlt

sum:
    push %bp                # 保存主调函数bp
    mov %sp, %bp            # 赋值被调函数bp为当前sp
    sub $8, %sp             # sp -= 8

    mov $1, %bx
    mov $0, %ax
1:
    add %bx, %ax
    inc %bx
    cmp $10, %bx
    jbe 1b

    mov %bp, %sp            # sp += 8, 释放被调函数栈空间
    pop %bp                 # 恢复主调函数bp
    ret

.org 0x1000
stack:
