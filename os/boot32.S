
.text
.code32

start32:
    # 保护模式
    mov $0x3f8, %dx
    mov $'P', %al
    out %al, %dx

    # 设置数据段寄存器
    mov $0x10, %ax
    mov %ax, %ds

    lgdt gdtr

    # 建立2级页表映射
    mov $0x32000, %edi
    mov $0x33000 + 3, %eax
1:
    stosl                       # (es:edi)=eax； edi+=4
    add $0x1000, %eax
    add $0x4, %edi
    cmp $(0x32000 + 32 * 8), %edi
    jl 1b

    # 建立1级页表映射
    mov $0x33000, %edi
    mov $0x0 + 3, %eax
2:
    stosl                       # (es:edi)=eax； edi+=4
    add $0x1000, %eax
    add $0x4, %edi
    cmp $(0x32000 + 512 * 32 * 8), %edi
    jl 2b

    hlt

gdt:
    .quad 0x0000000000000000
    .quad 0x00209a0000000000        # 64位模式下内核代码段描述符
    .quad 0x0000920000000000        # 64位模式下内核数据段描述符
gdt_end:

gdtr:
    .word gdt_end - gdt
    .long gdt           # 段基址是0，gdt地址就是gdt

# 4级页表
.org 0x10000
    .fill 511, 8, 0
    .quad 0x0000000000031003

# 3级页表
.org 0x11000
    .fill 509, 8, 0
    .quad 0x0000000000032003
    .fill 1, 8, 0

# 2级页表
.org 0x12000
    .fill 512, 8, 0

# 1级页表
.org 0x13000
    .fill 512 * 32, 8, 0
