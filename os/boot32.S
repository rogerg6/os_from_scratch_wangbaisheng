#
# 恒等映射是指虚拟地址等于物理地址，即VA=PA。
# 为什么需要恒等映射？目前保护模式所在的代码段没有做页表映射，在切换到64位模式后，
# 无法支撑从保护模式到64位模式的平滑过渡


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
    .quad 0x0000000000053003         # 恒等映射4级页表项
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

# 恒等映射3级页表
.org 0x33000
    .quad 0x0000000000054003
    .fill 511, 8, 0

# 恒等映射2级页表
.org 0x34000
    .quad 0x0000000000033003
    .fill 511, 8, 0