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
    mov $1, %bx
    mov $0, %ax
1:
    add %bx, %ax
    inc %bx
    cmp $10, %bx
    jbe 1b
    ret

.org 0x1000
stack: