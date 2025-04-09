kernel.bin: build boot16.bin boot32.bin system.bin app/app1.bin app/app2.bin
	./build

boot16.bin: boot16.S
	gcc -c boot16.S -o boot16.o
	ld -Ttext=0x0 boot16.o -o boot16.elf
	objcopy -O binary boot16.elf boot16.bin

boot32.bin: boot32.S
	gcc -c boot32.S -o boot32.o
	ld -Ttext=0x20000 boot32.o -o boot32.elf
	objcopy -O binary boot32.elf boot32.bin

CFLAGS = -std=c11 -I. -fno-pic -mcmodel=kernel -fno-stack-protector -fcf-protection=none \
	-nostdinc -fno-builtin

SRCS = main.c $(wildcard mm/*.c) $(wildcard lib/*.c) $(wildcard sched/*.c) $(wildcard kernel/*.c)

# 创建源文件的依赖关系
.depend: $(SRCS)
	@rm -f .depend
	@$(foreach src, $(SRCS), \
		echo -n $(dir $(src)) >> .depend; \
		gcc -I. -MM $(src) >> .depend; \
	)
include .depend

OBJS = $(SRCS:.c=.o)

system.bin: head64.o kernel/handler.o $(OBJS)
	gcc -c head64.S -o head64.o 
	gcc -c kernel/handler.S -o kernel/handler.o 
	ld -Ttext=0xffffffff80100000 $^ -o system.elf
	objcopy -O binary system.elf system.bin

app/libc/libc.o: app/libc/syscall.o
	# -r生成重定位目标文件
	ld -r -o $@ $^

app/app1.o: app/app1.c
	gcc -I. -c -o $@ $<

app/app1.bin: app/libc/start.o app/app1.o app/libc/libc.o
	ld -Ttext=0x100000 $^ -o app/app1.elf
	objcopy -O binary app/app1.elf $@

app/app2.bin: app/app2.o
	ld -Ttext=0x100000 $< -o app/app2.elf
	objcopy -O binary app/app2.elf $@

build: build.c
	gcc $< -o $@

compiledb:
	compiledb -nf -o ../compile_commands.json make

.PHONY: clean run

clean:
	find . -name "*.o" -o -name "*.elf" -o -name "*.bin" | xargs rm -f
	rm -f build .depend

run:
	../kvmtool/lkvm run -c 1 -k kernel.bin