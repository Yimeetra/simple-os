OBJS = \
	bootc.o \
	idt.o \
	interrupts_asm.o \
	interrupts.o \
	timer.o \
	io.o \
	switch.o \
	proc.o \
	gdt.o \
	string.o

CFLAGS += -ffreestanding
CFLAGS += -ffunction-sections
CFLAGS += -nostdlib
CFLAGS += -m32
CFLAGS += -fno-pie
CFLAGS += -falign-functions=4
CFLAGS += -O0
CFLAGS += -g

boot.bin: boot.asm
	nasm boot.asm -f bin -o boot.bin
	
interrupts_asm.o:
	nasm -f elf32 interrupts_asm.asm -g

switch.o:
	nasm -f elf32 switch.asm -g

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

show-functions:
	objdump -d kernel.o | grep '^.*>:' | cut -d ':' -f1