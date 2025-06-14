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

void puth(int number, char attr, int row, int col) {
    int len = 0;
    int number_copy = number;
    do {
        number_copy /= 16;
        len++;
    } while (number_copy != 0);

    for (int i = 0; i < len; ++i) {
        int remainder = number % 16;
        number /= 16;
        putc('0', attr, row, col);
        putc('x', attr, row, col+1);
        if (remainder < 10) {
            putc('0'+remainder, attr, row, col+len-i-1+2);
        } else {
            putc('a'+remainder-10, attr, row, col+len-i-1+2);
        }
    }
}

void putb(int number, char attr, int row, int col) {
    int len = 0;
    int number_copy = number;
    do {
        number_copy /= 2;
        len++;
    } while (number_copy != 0);

    for (int i = 0; i < len; ++i) {
        int remainder = number % 2;
        number /= 2;
        putc('0', attr, row, col);
        putc('b', attr, row, col+1);
        putc('0'+remainder, attr, row, col+len-i-1+2);
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

int sputd(char *dest, int number) {
    int len = 0;
    int number_copy = number;
    do {
        number_copy /= 10;
        len++;
    } while (number_copy != 0);

    for (int i = 0; i < len; ++i) {
        int remainder = number % 10;
        number /= 10;
        sputc(dest + len-i-1, '0'+remainder);
    }
    return len;
}

int sputh(char *dest, int number) {
    int len = 0;
    int number_copy = number;
    do {
        number_copy /= 16;
        len++;
    } while (number_copy != 0);

    sputc(dest + 0, '0');
    sputc(dest + 1, 'x');

    for (int i = 0; i < len; ++i) {
        int remainder = number % 16;
        number /= 16;
        if (remainder < 10) {
            sputc(dest + len-i-1+2, '0'+remainder);
        } else {
            sputc(dest + len-i-1+2, 'a'+remainder-10);
        }
    }
    return len+2;
}

int sputb(char *dest, int number) {
    int len = 0;
    int number_copy = number;
    do {
        number_copy /= 2;
        len++;
    } while (number_copy != 0);

    sputc(dest + 0, '0');
    sputc(dest + 1, 'b');

    for (int i = 0; i < len; ++i) {
        int remainder = number % 2;
        number /= 2;
        sputc(dest + len-i-1+2, '0'+remainder);
    }
    return len+2;
}

int sputc(char *dest, char ch) {
    *dest = ch;
    return 1;
}

int sputs(char *dest, char *string, int length) {
    for (int i = 0; i < length ; ++i) {
        sputc(dest + i, string[i]);
    }
    return length;
}