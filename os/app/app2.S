
1:
    mov $0x3f8, %dx
    mov $'B', %al
    out %al, %dx

    # syscall: sleep(1s)
    mov $1000, %rdi
    mov $0, %rax
    syscall

    jmp 1b