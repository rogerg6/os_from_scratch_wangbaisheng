#include "app/libc/std.h"
#include "app/libc/print.h"
#include "app/libc/types.h"
#include "app/libdraw/draw.h"

void draw_char(uint64_t fbaddr, struct mode_info *minfo, int color) {
    draw_char_en(10, 2, 0, color, fbaddr, minfo);
    draw_char_en(20, 2, 1, color, fbaddr, minfo);
    draw_char_en(30, 2, 2, color, fbaddr, minfo);
    draw_char_en(40, 2, 2, color, fbaddr, minfo);
    draw_char_en(50, 2, 3, color, fbaddr, minfo);
    draw_char_en(60, 2, 4, color, fbaddr, minfo);

    draw_char_zh(70, 2, 0, color, fbaddr, minfo);
    draw_char_zh(90, 2, 1, color, fbaddr, minfo);
    draw_char_en(110, 2, 5, color, fbaddr, minfo);
}

int main(void) {
    void *m = shm_open("shm-1");

    struct mode_info minfo;
    get_mode_info(&minfo);

    unsigned long fbbase = fbmap();
    draw_char(fbbase, &minfo, RED | GREEN);

    unsigned long i = 0;
    while (1) {
        if (i % 2)
            draw_char(fbbase, &minfo, RED | GREEN);
        else
            draw_char(fbbase, &minfo, RED | BLUE);
        i++;

        print(*(char*)m);
        sleep(1000);
    }
    return 0;
}