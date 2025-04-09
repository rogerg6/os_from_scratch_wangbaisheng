#include "app/libc/std.h"
#include "app/libc/print.h"

int main(void) {
    void *m = shm_open("shm-1");

    while (1) {
        print(*(char*)m);
        sleep(1000);
    }
    return 0;
}