#include "include/vesa.h"
#include "include/mm.h"
#include "include/string.h"
#include "include/sched.h"

struct vesa_mode_info *vesa_mode_info;

void vesa_init(void) {
    vesa_mode_info = malloc(sizeof(vesa_mode_info));
    memcpy(vesa_mode_info, (char*)0x14000, sizeof(struct vesa_mode_info));
    print('z');
}

/**
 * @brief 应用空间映射显存
 */
unsigned long do_fbmap(void) {
    unsigned long va = 0xe000000;       // framebuffer虚拟基址
    unsigned long pa = vesa_mode_info->fbbase;

    unsigned long npixel = vesa_mode_info->hres * vesa_mode_info->vres \
        * vesa_mode_info->bpp / 8;

    map_range(current->pml4, va, (unsigned long)pa, 0x4,
        (npixel + PAGE_SIZE - 1) / PAGE_SIZE);
    
    return va;
}

int do_get_mode_info(struct mode_info *mode_info) {
    mode_info->fbbase = vesa_mode_info->fbbase;
    mode_info->hres = vesa_mode_info->hres;
    mode_info->vres = vesa_mode_info->vres;
    mode_info->bpp = vesa_mode_info->bpp;
    return 0;
}