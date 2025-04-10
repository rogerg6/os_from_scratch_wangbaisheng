#include "include/types.h"

struct vesa_mode_info {
    uint8_t pad0[18];
    uint16_t hres;          // horizonal resolution
    uint16_t vres;          // vertical resolution

    uint8_t pad1[3];
    uint8_t bpp;            // bits per pixel
    uint8_t pad2[14];

    uint32_t fbbase;        // framebuffer base addr
    uint8_t pad3[212];
} __attribute__((packed));


struct mode_info {
    uint32_t fbbase;        // framebuffer base addr
    uint16_t hres;          // horizonal resolution
    uint16_t vres;          // vertical resolution
    uint8_t bpp;            // bits per pixel
};


void vesa_init(void);