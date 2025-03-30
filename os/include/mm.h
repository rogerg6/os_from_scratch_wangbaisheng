#include "types.h"

#define E820MAX 32

struct e820entry {
    uint64_t addr;
    uint64_t size;
    uint32_t type;
} __attribute__((packed));

struct e820map {
    uint32_t nr_entry;
    struct e820entry map[E820MAX];
};
