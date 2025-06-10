OBJS = \
	bootc.o \
	idt.o \
	irqs.o \
	interrupts.o \
	timer.o

CFLAGS += -ffreestanding
CFLAGS += -ffunction-sections
CFLAGS += -nostdlib
CFLAGS += -m32
CFLAGS += -fno-pie
CFLAGS += -falign-functions=4
CFLAGS += -O0

boot.bin: boot.asm
	nasm boot.asm -f bin -o boot.bin
	
irqs.o:
	nasm -f elf32 irqs.asm

kernel.o: $(OBJS)
	ld -T kernel.ld $(OBJS) -o kernel.o --build-id=none

kernel.bin: kernel.o
	objcopy -O binary kernel.o kernel.bin

image.bin: boot.bin kernel.bin
	cat boot.bin kernel.bin > image.bin

run-gdb: image.bin
	qemu-system-i386 -fda image.bin -s -S

run: image.bin
	qemu-system-i386 -fda image.bin -s

gdb:
	gdb -q -x qemu.gdb

clean:
	rm *.o
	rm *.bin