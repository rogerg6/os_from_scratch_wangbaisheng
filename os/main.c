
extern void mm_init(void);

int main(void) {
    __asm__(
        "mov $0x3f8, %dx\n\t"
        "mov $'M', %ax\n\t"
        "out %ax, %dx\n"
    );
    mm_init();
    __asm__("hlt");
}