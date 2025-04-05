

#include "include/types.h"
#include "include/string.h"
#include "include/segment.h"


#define GATE_INTERRUPT 0xe
#define GATE_EXCEPTION 0xf

/**
 * @brief 中断描述符
 * offset 中断处理函数地址
 * segment 段选择子
 * ist     中断栈索引
 * type    中断 or 异常
 * dpl     特权级
 * p       存在位
 * 
 */
struct gate_desc {
    uint16_t offset_low;
    uint16_t segment;
    uint16_t ist:3, zero:5, type:4, zero2:1, dpl:2, p:1;
    uint16_t offset_middle;
    uint16_t offset_high;
    
    uint32_t reserved;
} __attribute__((packed));

/**
 * 中断描述符表 IDT
 */
struct gate_desc idt_table[256];


/**
 * @brief 设置gate descriptor.
 * @param index: 中断号
 * @param addr : 中断处理函数地址
 * @param type : 描述符类型，中断或异常
 */
static void set_gate(unsigned char index, unsigned long addr, char type) {
    struct gate_desc *desc = &idt_table[index];

    memset(desc, 0, sizeof(struct gate_desc));
    desc->segment = KERNEL_CS;
    desc->offset_low = (uint16_t)addr;
    desc->offset_middle = (uint16_t)(addr >> 16);
    desc->offset_high = (uint16_t)(addr >> 32);
    // desc->ist = ;               //中断不用中断栈，用进程内核栈
    desc->dpl = 0;
    desc->type = type;
    desc->p = 1;
}