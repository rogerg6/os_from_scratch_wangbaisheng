#include "types.h"

#define IO_BITMAP_BYTES   (65536 / 8)

// 任务状态段
struct tss {
    uint32_t reserved1;
    uint64_t rsp0;          // 特权级0内核栈
    uint64_t rsp1;          // 特权级1内核栈
    uint64_t rsp2;          // 特权级2内核栈
    uint64_t reserved2;
    uint64_t ist[7];        // 中断栈表
    uint32_t reserved3;
    uint32_t reserved4;
    uint16_t reserved5;
    uint16_t io_bitmap_offset;                      // IO权限位图相对tss基址偏移
    uint8_t io_bitmap[IO_BITMAP_BYTES + 1];         // IO权限位图
} __attribute__((packed));


/**
 * @brief 任务状态段描述符
 * base     tss基址
 * limit    tss长度
 * desc_type    段描述符类型
 * dpl      段特权级字段
 * p        存在位
 * avl      系统软件使用位
 * g        粒度
*/
struct tss_desc {
    uint16_t limit0;
    uint16_t base0;
    uint16_t base1:8, type:4, desc_type:1, dpl:2, p:1;
    uint16_t limit1:4, avl:1, zero0:2, g:1, base2:8;
    uint32_t base3;
    uint32_t zero1;
}__attribute__((packed));

extern struct tss tss;


void tss_init(void);


