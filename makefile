CC = bcc
LD = ld86
ASM = nasm

CFLAGS = -ansi -I./include -c
ASMFLAGS_BOOT = -f bin
ASMFLAGS_KERNEL = -f as86
LDFLAGS = -d

all: build

prepare:
	mkdir -p bin
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	$(ASM) $(ASMFLAGS_BOOT) src/bootloader.asm -o bin/bootloader.bin
	dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc

stdlib:
	$(CC) $(CFLAGS) src/std_lib.c -o bin/std_lib.o

shell: stdlib
	$(CC) $(CFLAGS) src/shell.c -o bin/shell.o

kernel: stdlib
	$(CC) $(CFLAGS) src/kernel.c -o bin/kernel.o
	$(ASM) $(ASMFLAGS_KERNEL) src/kernel.asm -o bin/kernel_asm.o

link: kernel shell
	$(LD) $(LDFLAGS) -o bin/kernel.bin bin/kernel.o bin/kernel_asm.o bin/std_lib.o bin/shell.o
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 conv=notrunc

build: prepare bootloader link

clean:
	rm -f bin/*.o bin/*.bin bin/floppy.img
