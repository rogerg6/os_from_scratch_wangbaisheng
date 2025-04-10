#include "app/libc/std.h"
#include "app/libc/print.h"
#include "app/libdraw/draw.h"

int main(void) {
        print('A');
    void *m = shm_open("shm-1");
    *(char*)m = 'S';

    struct mode_info minfo;
    get_mode_info(&minfo);

    unsigned long fbbase = fbmap();

    while (1) {

        draw_rect(10, 100, 150, 100, RED, fbbase, &minfo);
        print('B');
        sleep(1000);
        draw_rect(10, 100, 150, 100, GREEN, fbbase, &minfo);
        sleep(1000);
        draw_rect(10, 100, 150, 100, BLUE, fbbase, &minfo);
        sleep(1000);
    }
    return 0;
}