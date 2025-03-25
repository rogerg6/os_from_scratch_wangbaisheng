# 立即数寻址
# 直接把立即数赋值给寄存器
.text
.code16
start:
    mov $0x41, %al
    jmp 1f
    mov $0x42, %al

1:
    mov $0x3f8, %dx
    out %al, %dx
    hlt