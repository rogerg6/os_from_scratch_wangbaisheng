.text
.code16
start:
  mov $0x1010, %bx
  mov %bx, %es

  mov $0x3f8, %dx

  mov 0x100, %al
  out %al, %dx

  mov %es:0x100, %al
  out %al, %dx
  hlt

.org 0x100
  .byte 0x41
.org 0x200
  .byte 0x42
