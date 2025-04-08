
1:
    mov $0x3f8, %dx
    mov $'B', %al
    out %al, %dx

    jmp 1b