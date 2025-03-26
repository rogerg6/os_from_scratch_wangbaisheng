.text
.code16
.global sum                 # 伪指令，告诉汇编器sum是全局可见符号

sum:
    push %bp                # 保存主调函数bp
    mov %sp, %bp            # 赋值被调函数bp为当前sp
    sub $2, %sp             # sp -= 2, 局部变量，用来存储累加值。相当于int sum;
    
    push %bx                # 保存寄存器

    mov $1, %bx
    movw $0, -2(%bp)        # 通过bp指针来寻址局部变量
1:
    add %bx, -2(%bp)
    inc %bx
    #cmp 4(%bp), %bx         # 比较主调函数传入的参数
    cmp %di, %bx
    jbe 1b

    mov -2(%bp), %ax

    pop %bx                 # 恢复寄存器

    mov %bp, %sp            # sp += 8, 释放被调函数栈空间
    pop %bp                 # 恢复主调函数bp
    ret
