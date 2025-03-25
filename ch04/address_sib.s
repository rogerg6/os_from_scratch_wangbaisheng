# SIB寻址
# 以一维数组为例，每个数组元素的地址=数组基址 + 元素大小 * 索引
# 即：Base + Scale * Index
# SIB寻址的语法是：(base, index, scale)
#
# 下面以1+2+...+10为例

.text
.code16
start:
    mov $var, %ebx
    mov $0, %esi
    mov $0, %ax

1:
    add (%ebx, %esi, 2), %ax        # ax=*(ebx + esi * 2)
    add $1, %esi
    cmp $10, %esi
    jb 1b

    mov $0x3f8, %dx
    out %ax, %dx

    hlt

var:
    .word 1
    .word 2
    .word 3
    .word 4
    .word 5
    .word 6
    .word 7
    .word 8
    .word 9
    .word 10
