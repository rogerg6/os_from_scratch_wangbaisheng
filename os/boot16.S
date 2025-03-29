
.text
.code16

.start16:
    # 实模式
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