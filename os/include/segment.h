
#define KERNEL_CS 0x8
#define KERNEL_DS 0x10

#define USER32_CS 0x1b
#define USER_DS   0x23
#define USER_CS   0x2b

#define GDT_TSS_ENTRY 6     // tss描述符在gdt中的索引