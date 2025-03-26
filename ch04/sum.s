.text
.code16
.global sum                 # 伪指令，告诉汇编器sum是全局可见符号

sum:
    push %bp                # 保存主调函数bp
    mov %sp, %bp            # 赋值被调函数bp为当前sp
    sub $8, %sp             # sp -= 8

    mov $1, %bx
    mov $0, %ax
1:
    add %bx, %ax
    inc %bx
    #cmp 4(%bp), %bx         # 比较主调函数传入的参数
    cmp %di, %bx
    jbe 1b

    mov %bp, %sp            # sp += 8, 释放被调函数栈空间
    pop %bp                 # 恢复主调函数bp
    ret
