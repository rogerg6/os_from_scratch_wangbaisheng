#include "app/libdraw/draw.h"

extern uint8_t fonts_en[6][16];
extern uint8_t fonts_zh[2][32];

void draw_char_en(int o_x, int o_y, int index, int color, 
        unsigned long fbbase, struct mode_info *minfo) {
    for (int y = 0; y < 16; y++) {
        char c = fonts_en[index][y];

        for (int x = 0; x < 8; x++) {
            char bit = (c >> (7 - x)) & 0x1;
            if (bit == 1) {
                *((uint32_t*)fbbase + (o_y + y) * minfo->hres +
                    o_x + x) = color;
            }
        }
    }
}

void draw_char_zh(int o_x, int o_y, int index, int color, 
        unsigned long fbbase, struct mode_info *minfo) {
    for (int y = 0; y < 16; y++) {
        char c1 = fonts_zh[index][y * 2];
        for (int x = 0; x < 8; x++) {
            char bit = (c1 >> (7 - x)) & 0x1;
            if (bit == 1) {
                *((uint32_t*)fbbase + (o_y + y) * minfo->hres +
                    o_x + x) = color;
            }
        }

        c1 = fonts_zh[index][y * 2 + 1];
        for (int x = 0; x < 8; x++) {
            char bit = (c1 >> (7 - x)) & 0x1;
            if (bit == 1) {
                *((uint32_t*)fbbase + (o_y + y) * minfo->hres +
                    o_x + 8 + x) = color;
            }
        }

    }
}

void draw_rect(int o_x, int o_y, int h, int w, int color,
        unsigned long fbbase, struct mode_info *minfo) {
    for (int x = 0; x < w; x++) {
        *((uint32_t*)fbbase + o_y * minfo->hres + o_x + x) = color;
        *((uint32_t*)fbbase + (o_y + h - 1) * minfo->hres + o_x + x) = color;
    }
    for (int y = 0; y < h; y++) {
        *((uint32_t*)fbbase + (o_y + y) * minfo->hres + o_x) = color;
        *((uint32_t*)fbbase + (o_y + y) * minfo->hres + o_x + w - 1) = color;
    }
}