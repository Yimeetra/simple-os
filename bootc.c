#include "interrupts.h"
#include "inline_asm.h"
#include "timer.h"

void main() {
    interrupts_init();
    pit_set_frequency(1000);
    __asm__ volatile("sti");

    clear();
    
    while (1);
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
