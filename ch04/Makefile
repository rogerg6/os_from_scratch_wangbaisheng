
all:
	as hello_use_segmentreg.s -o hello.o
	ld -Ttext=0 hello.o -o hello.elf
	objcopy -O binary hello.elf hello.bin

dump:
	objdump -d -m i8086 hello.elf

run:
	# 用机器码写程序, 程序不断打印字符A
	../kvmtool/lkvm run -c 1 -k hello.bin

clean:
	rm *.o *.bin *.elf