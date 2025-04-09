#include "app/libc/std.h"
#include "app/libc/print.h"

int main(void) {
    while (1) {
        print('A');
        sleep(1000);
    }
    return 0;
}