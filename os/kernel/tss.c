
#include "include/tss.h"
#include "include/string.h"
#include "include/sched.h"
#include "include/segment.h"
#include "include/print.h"

struct tss tss;
extern unsigned long gdt[64];

void tss_init(void) {
    /* 初始化tss */
    memset(&tss, 0, sizeof(struct tss));
    tss.rsp0 = current->kstack;
    tss.io_bitmap_offset = __builtin_offsetof(struct tss, io_bitmap_offset);
    tss.io_bitmap[IO_BITMAP_BYTES] = 0xff;

    /**
     * just for test
     * IO权限设置为1，表示禁止所有IO权限
     */
    // memset(tss.io_bitmap, 0xff, IO_BITMAP_BYTES);

    /* 初始化tss段描述符 */
    struct tss_desc *desc = (struct tss_desc *)&gdt[GDT_TSS_ENTRY];
    memset(desc, 0, sizeof(struct tss_desc));
    desc->limit0 = sizeof(tss) & 0xffff;
    desc->base0 = (unsigned long)(&tss) & 0xffff;
    desc->base1 = ((unsigned long)(&tss) >> 16) & 0xff;
    desc->type = 0x9;
    desc->p = 1;
    desc->limit1 = (sizeof(tss) >> 16) & 0xf;
    desc->base2 = ((unsigned long)(&tss) >> 24) & 0xff;
    desc->base3 = (unsigned long)(&tss) >> 32;

    /* 设置任务寄存器, 指向gdt表中的tss_desc */
    __asm__("ltr %w0" : : "r"(GDT_TSS_ENTRY << 3));
}