.text
.code16
start:
  mov $'A', %al
  mov $0x3f8, %dx
  out %al, %dx
  hlt
