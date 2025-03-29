.text
.code64

start64:
    # 64位模式
    mov $0x3f8, %dx
    mov $'L', %al
    out %al, %dx

    hlt