# 栈

.text
.code16

start:
    #mov $0x2000, %ax
    #mov %ax, %ss
    mov $stack, %sp
    mov $0x3f8, %dx

    push $0x41          # push一个word，即2byte
    push $0x42

    #mov %ss:0xffe, %ax
    mov 0x1000-2, %ax
    out %ax, %dx

    #mov %ss:0xffc, %ax
    mov 0x1000-4, %ax
    out %ax, %dx

    pop %ax
    out %ax, %dx
    
    pop %ax
    out %ax, %dx
    
    hlt

.org 0x1000
stack:
