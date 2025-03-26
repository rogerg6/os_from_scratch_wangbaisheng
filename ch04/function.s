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

.org 0x1000
stack:
