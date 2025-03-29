/**
1. 内核映像(kernel.bin)布局

          +------------+------------+------------+
 offset   |     0x0    |  0x10000   |  0xf0000   |
          +------------+------------+------------+
 text     | boot16.bin | boot32.bin | system.bin |
          +------------+------------+------------+

2. 内核加载到内存的布局

          +------------+------------+------------+
  PA      |   0x10000  |  0x20000   |  0x100000  |
          +------------+------------+------------+
 text     | boot16.bin | boot32.bin | system.bin |
          +------------+------------+------------+

*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// kvmtool默认加载到0x1000:0, 即物理地址0x10000处
#define BOOT16_START_ADDR   0x10000          // boot16.bin加载物理地址
#define BOOT32_START_ADDR   0x20000          // boot32.bin加载物理地址
#define SYSTEM_START_ADDR   0x100000         //system.bin加载物理地址

int main(void) {
    int fd_out;
    int fd;
    char buf[512];
    int c;

    fd_out = open("kernel.bin", O_WRONLY | O_CREAT, 0664);
    if (fd_out < 0) {
        fprintf(stderr, "create kernel.bin failed.\n");
        return -1;
    }

    // read boot16.bin
    fd = open("boot16.bin", O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "open boot16.bin failed.\n");
        return -2;
    }
    while (1) {
        c = read(fd, buf, 512);
        if (c > 0)
            write(fd_out, buf, c);
        else
            break;
    }
    close(fd);

    lseek(fd_out, BOOT32_START_ADDR - BOOT16_START_ADDR, SEEK_SET);

    // read boot32.bin
    fd = open("boot32.bin", O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "open boot32.bin failed.\n");
        return -3;
    }
    while (1) {
        c = read(fd, buf, 512);
        if (c > 0)
            write(fd_out, buf, c);
        else
            break;
    }
    close(fd);

    lseek(fd_out, SYSTEM_START_ADDR - BOOT16_START_ADDR, SEEK_SET);

    // read system
    fd = open("system.bin", O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "open system.bin failed.\n");
        return -3;
    }
    while (1) {
        c = read(fd, buf, 512);
        if (c > 0)
            write(fd_out, buf, c);
        else
            break;
    }
    close(fd);

    close(fd_out);
    return 0;
}