# 直接寻址
# 操作数是一个内存地址。实际操作的是地址处的值

.text
.code16
start:
    mov var, %al            # al=*(var)
    mov $0x3f8, %dx
    out %al, %dx
    hlt

.org 20
var:
    .byte 0x41