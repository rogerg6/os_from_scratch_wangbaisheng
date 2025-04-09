
#include "include/segment.h"
#include "include/types.h"
#include "include/print.h"

#define MSR_STAR            0xc0000081
#define MSR_LSTAR           0xc0000082
#define MSR_SYSCALL_MASK    0xc0000084

#define RF_IF               0x00000200

extern void system_call(void);
typedef unsigned long (*fn_ptr)(void);

unsigned long do_sleep(unsigned long ms);
int do_shm(char *name);

fn_ptr syscall_table[] = {
        do_sleep,
        do_shm
};

void syscall_init(void) {
    uint64_t star = (uint64_t)USER32_CS << 48 | (uint64_t)KERNEL_CS << 32;
    uint64_t lstar = (uint64_t)system_call;
    uint64_t syscall_mask = RF_IF;

    __asm__("wrmsr":: "c"(MSR_STAR),
            "a"((uint32_t)star), "d"(star >> 32));
    __asm__("wrmsr":: "c"(MSR_LSTAR),
            "a"((uint32_t)lstar), "d"(lstar >> 32));
    __asm__("wrmsr":: "c"(MSR_SYSCALL_MASK),
            "a"((uint32_t)syscall_mask), "d"(syscall_mask >> 32));
}
