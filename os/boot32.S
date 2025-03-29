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
    mov %ax, %es                # 初始化各个段寄存器
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    lgdt gdtr

    # 建立2级页表映射
    mov $0x32000, %edi
    mov $0x33000 + 3, %eax
1:
    stosl                       # (es:edi)=eax； edi+=4
    add $0x1000, %eax
    add $4, %edi
    cmp $(0x32000 + 32 * 8), %edi
    jl 1b

    # 建立1级页表映射
    mov $0x33000, %edi
    mov $0x0 + 3, %eax
2:
    stosl                       # (es:edi)=eax； edi+=4
    add $0x1000, %eax
    add $4, %edi
    cmp $(0x32000 + 512 * 32 * 8), %edi
    jl 2b

    ##### 切换到64位模式 #####
    # 1. 设置CR4 PAE位，使能x86物理地址扩展功能
    mov %cr4, %eax
    btsl $5, %eax               # bts(bit set)可单独置位寄存器某一位
    movl %eax, %cr4

    # 2. 设置CR3指向页表
    movl $0x30000, %eax
    movl %eax, %cr3

    # 3. 使能64位模式
    movl $0xc0000080, %ecx
    rdmsr
    bts $8, %eax            # 使能64位模式。使能并不代表进入64位模式!!!! 在开启分页后，cpu才会自动进入64位模式
    bts $0, %eax            # 使能syscall指令
    wrmsr

    # 4. 开启分页。激活64位模式
    mov %cr0, %eax
    bts $31, %eax
    mov %eax, %cr0

    ##### 跳转到head64.S #####
    ljmp $0x8, $0x100000


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
    .fill 510, 8, 0
    .quad 0x0000000000031003

# 3级页表
.org 0x11000
    .fill 510, 8, 0
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