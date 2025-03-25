# SIB + disp寻址
# 以二维数组为例，和一维数组不同的是：每个数组元素的地址=行基址 + 元素大小 * 索引
# 即：Base + Scale * Index
# 但是需要记录整个二维数组在段中的偏移disp。所以：
# SIB+disp寻址的语法是：disp(base, index, scale)
#
# 下面计算3x3的二维数组为例，计算所有行的第2列的值。

.text
.code16
start:
    mov $0, %ebx
    mov $1, %esi
    mov $0, %ax

1:
    add var(%ebx, %esi, 2), %ax        # ax=*(var + ebx + esi * 2)
    add $6, %ebx
    cmp $12, %ebx
    jbe 1b

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
