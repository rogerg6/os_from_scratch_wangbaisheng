
.text
.code32

start32:
    # 保护模式
    mov $0x3f8, %dx
    mov $'P', %al
    out %al, %dx

    hlt