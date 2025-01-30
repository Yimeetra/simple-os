OBJS = \
	bootc.o

CFLAGS += -ffreestanding
CFLAGS += -nostdlib
CFLAGS += -m16
CFLAGS += -fno-pie

boot.bin: boot.asm
	nasm boot.asm -f bin -o boot.bin

kernel.bin: $(OBJS)
	ld -T kernel.ld $(OBJS) -o kernel.bin

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