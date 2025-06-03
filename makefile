CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -c
LD = ld
LDFLAGS = -m elf_i386 -Ttext 0x1000
ASM = nasm
ASMFLAGS = -f elf

all: build

prepare:
	dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
	$(ASM) src/bootloader.asm -o bin/bootloader.bin
	dd if=bin/bootloader.bin of=bin/floppy.img conv=notrunc

stdlib:
	$(CC) $(CFLAGS) src/std_lib.c -o bin/std_lib.o

shell:
	$(CC) $(CFLAGS) src/shell.c -o bin/shell.o

kernel:
	$(CC) $(CFLAGS) src/kernel.c -o bin/kernel.o
	$(ASM) $(ASMFLAGS) src/kernel.asm -o bin/kernel_asm.o

link:
	$(LD) $(LDFLAGS) -o bin/kernel.bin bin/kernel.o bin/kernel_asm.o bin/std_lib.o bin/shell.o
	dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 conv=notrunc

build: prepare bootloader stdlib shell kernel link

clean:
	rm -f bin/*.o bin/*.bin bin/floppy.img
