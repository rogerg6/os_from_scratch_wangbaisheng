#define IO_PIC 0x20
#define IRQ_OFFSET 32

.text
.code16

.start16:
    ##### 实模式 #####
    
    # 调用BIOS中断，获取内存信息
    # 存放在0x13000处
    mov $e820_entry, %di
    xor %ebx, %ebx
e820_read_entry:
    mov $0xe820, %eax
    mov $20, %ecx
    int $0x15

    incb e820_nr_entry
    add  $20, %di

    cmp $0, %ebx
    jne e820_read_entry

    # 初始化8259A中断芯片
    # ICW1
    mov $0x13, %al
    mov $(IO_PIC), %dx
    out %al, %dx

    # ICW2
    mov $(IRQ_OFFSET), %al
    mov $(IO_PIC + 1), %dx
    out %al, %dx

    # ICW4
    mov $0x1, %al
    mov $(IO_PIC + 1), %dx
    out %al, %dx

    lgdt gdtr               # 告知cpu段描述符地址

    # 切换cpu到保护模式
    mov %cr0, %eax
    or $0x1, %eax
    mov %eax, %cr0

    # 此时，cpu是保护模式，但是代码还是实模式,
    # 所以需要跳转到保护模式代码. 由于cpu是保护模式
    # 所以目的地址需要用保护模式下的方式来寻址
    # 段选择子 + 段内偏移
    ljmpl $0x8, $0x20000

gdt:
    .quad 0x0000000000000000
    .quad 0x00c09a00000007ff        # 保护模式下内核代码段描述符
    .quad 0x00c09200000007ff        # 保护模式下内核数据段描述符
gdt_end:

gdtr:
    .word gdt_end - gdt
    .word gdt, 0x1

.org 0x3000
e820_nr_entry:
    .long 0
e820_entry:
    .fill 1024, 1, 0