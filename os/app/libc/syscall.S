# 把平台相关的系统调用代码封装到该文件中
# 达到和app代码解耦的目的

#define SYSCALL_SLEEP           0
#define SYSCALL_SHM             1
#define SYSCALL_FBMAP           2
#define SYSCALL_GETMODEINFO     3

.globl sleep
.globl shm_open
.globl fbmap
.globl get_mode_info

sleep:
    mov $SYSCALL_SLEEP, %rax
    syscall
    ret

shm_open:
    mov $SYSCALL_SHM, %rax
    syscall
    ret

fbmap:
    mov $SYSCALL_FBMAP, %rax
    syscall
    ret

get_mode_info:
    mov $SYSCALL_GETMODEINFO, %rax
    syscall
    ret

