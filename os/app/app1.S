
.text
.code64

1:
    mov $0x3f8, %dx
    mov $'A', %ax
    out %ax, %dx

#    movb $'F', (0x12345678)
#    mov (0x12345678), %al
#
#    mov $0x3f8, %dx
#    out %al, %dx
#
    jmp 1b