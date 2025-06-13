#include "io.h"

void putd(int number, char attr, int row, int col) {
    int len = 0;
    int number_copy = number;
    do {
        number_copy /= 10;
        len++;
    } while (number_copy != 0);

    for (int i = 0; i < len; ++i) {
        int remainder = number % 10;
        number /= 10;
        putc('0'+remainder, attr, row, col+len-i-1);
    }
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