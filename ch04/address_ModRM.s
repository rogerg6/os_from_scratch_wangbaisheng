# Mod R/M寻址

.text
.code16
start:
    mov $0x3f8, %dx
    mov $var1, %bx

    mov (%bx), %al              # al=*(cs:bx)=*(cs:0x50)
    out %al, %dx

    mov 0x10(%bx), %al          # al=*(cs:(bx+10))=*(cs:0x60)
    out %al, %dx

    mov %bl, %al

    hlt

.org 0x50
var1:
    .byte 0x41

.org 0x60
var2:
    .byte 0x42