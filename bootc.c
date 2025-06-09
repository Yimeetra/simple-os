#include "idt.h"

void isr0_handler();

void main() {
    idt_init();
    idt_add_gate(0, isr0_handler, 0x0008, 0x8E);

    clear();

    __asm__ volatile("int $0");

    while (1);
}

void isr0_handler() {
    putc('0', 0x0f, 0, 0);
}



void putc(char ch, char attr, int row, int col) {
    short *video = (short*) 0xb8000;
    video[row*80+col] = (short) attr << 8 | ch;
}

void puts(char *string, int length, char attr, int row, int col) {
    for (int i = 0; i < length ; ++i) {
        putc(string[i], attr, row+i/80, col+i);
    }
}

void clear() {
    short *video = (short*) 0xb8000;
    for (int i = 0; i < 80*25; ++i) {
        video[i] = 0x0000;
    }
}
