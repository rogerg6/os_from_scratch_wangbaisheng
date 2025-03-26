# 函数
# x86调用约定
#
# 参数传递，参数列表从右到左一次传递。可以有2种方法
# 1. 栈传递
#    参数保存在主调函数栈帧，地址从低到高依次是param1, param2...paramn
#    通过被调函数的bp指针为锚点可以很方便的访问到这些参数
#
# 2. 寄存器传递
#    效率比栈高。x86的64位模式下，依次用rdi, rsi, rdx, rcx, r8-9传递参数

.text
.code16

start:
    mov $stack, %sp         # 初始化栈指针
    #push $50                # 用栈传递参数，sum(50)
    mov $50, %di            # 用di传递参数
    call sum

    mov $0x3f8, %dx
    out %ax, %dx
    hlt

.org 0x1000
stack:
