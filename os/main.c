#include "include/mm.h"


int main(void) {
    __asm__(
        "mov $0x3f8, %dx\n\t"
        "mov $'M', %ax\n\t"
        "out %ax, %dx\n"
    );
    mm_init();

    unsigned long *x = VA(200 * 1024 * 1024);
    *x = 5;
    print(*x);

    __asm__("hlt");
}