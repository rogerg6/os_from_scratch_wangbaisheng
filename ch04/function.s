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
#
# 返回值传递一般用AX
#
# 寄存器保存恢复
#               主调保存                被调保存
# 32bit        eax edx ecx           ebx edi esi ebp
# 64bit    rdi rsi rdx rcx r8~11     rbx rbp r12~15
# 
# +--------------+
# |主调保存寄存器 |
# +--------------+    主调栈帧
# |  被调函数参数 |
# +--------------+----------------
# |   返回地址    |
# +--------------+    被调栈帧
# |  主调函数BP   |
# +--------------+ <--- BP
# |   局部变量    |
# +--------------+
# |被调保存寄存器 |
# +--------------+ <--- SP

.text
.code16

start:
    mov $stack, %sp         # 初始化栈指针

    # 调用sum前，给bx，cx赋值
    # 调用sum后，打印bx，cx的值
    # sum中使用了bx，所以需要调用前后保存、恢复bx
    mov $0x41, %bx
    mov $0x42, %cx

    push %cx

    #push $50                # 用栈传递参数，sum(50)
    mov $50, %di            # 用di传递参数
    call sum

    pop %cx

    mov $0x3f8, %dx
    out %ax, %dx

    mov %bx, %ax
    out %ax, %dx
    mov %cx, %ax
    out %ax, %dx
    
    hlt

.org 0x1000
stack:
