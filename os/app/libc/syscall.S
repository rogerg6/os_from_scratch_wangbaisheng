# 把平台相关的系统调用代码封装到该文件中
# 达到和app代码解耦的目的

#define SYSCALL_SLEEP           0

.globl sleep

sleep:
    mov $SYSCALL_SLEEP, %rax
    syscall
    ret