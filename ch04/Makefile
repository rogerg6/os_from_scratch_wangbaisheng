
all: hello addr_immd addr_disp addr_modrm addr_sib addr_sib_disp stack \
func

hello:
	as hello_use_segmentreg.s -o hello.o
	ld -Ttext=0 hello.o -o hello.elf
	objcopy -O binary hello.elf hello.bin

addr_immd:
	as address_immd.s -o addr_immd.o
	ld -Ttext=0 addr_immd.o -o addr_immd.elf
	objcopy -O binary addr_immd.elf addr_immd.bin

addr_disp:
	as address_disp.s -o addr_disp.o
	ld -Ttext=0 addr_disp.o -o addr_disp.elf
	objcopy -O binary addr_disp.elf addr_disp.bin

addr_modrm:
	as address_ModRM.s -o addr_ModRM.o
	ld -Ttext=0 addr_ModRM.o -o addr_ModRM.elf
	objcopy -O binary addr_ModRM.elf addr_ModRM.bin

addr_sib:
	as address_sib.s -o addr_sib.o
	ld -Ttext=0 addr_sib.o -o addr_sib.elf
	objcopy -O binary addr_sib.elf addr_sib.bin

addr_sib_disp:
	as address_sib_disp.s -o addr_sib_disp.o
	ld -Ttext=0 addr_sib_disp.o -o addr_sib_disp.elf
	objcopy -O binary addr_sib_disp.elf addr_sib_disp.bin

stack:
	as stack.s -o stack.o
	ld -Ttext=0 stack.o -o stack.elf
	objcopy -O binary stack.elf stack.bin

func:
	as function.s -o func.o
	as sum.s -o sum.o
	ld -Ttext=0 func.o sum.o -o func.elf
	objcopy -O binary func.elf func.bin

dump:
	objdump -d -m i8086 hello.elf

run:
	../kvmtool/lkvm run -c 1 -k addr_immd.bin

clean:
	rm *.o *.bin *.elf