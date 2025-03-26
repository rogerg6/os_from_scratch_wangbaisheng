/**
 * C语言内联汇编
 * 语法：
 *      asm (
 *          汇编指令
 *          : 输出操作数列表
 *          : 输入操作数列表
 *          : 汇编指令修改的寄存器和内存列表
 *      )     
 *
**/
#include <stdio.h>

int main() {
    int x = 2;
    int y = 3;
    int sum = 0;

    // sum = x + y
    asm (
        "mov %1, %%eax\n\t"                 // %1 引用x
        "mov %[addend], %%ebx\n\t"          // %[addend]引用y。addend是y的汇编名字
        "add %%ebx, %%eax\n\t"
        "mov %%eax, %0"                     // %0引用sum
        :"=m"(sum)
        :"m"(x), [addend]"m"(y)
        :"eax", "ebx", "r11", "r12"         // 内联汇编中用到的寄存器，告诉编译器需要保存恢复
    );

    printf("sum = %d\n", sum);
    return 0;
}