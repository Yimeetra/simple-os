void main() {
    putc('H', 0x07, 0, 0);
    putc('e', 0x07, 0, 1);
    putc('l', 0x07, 0, 2);
    putc('l', 0x07, 0, 3);
    putc('o', 0x07, 0, 4);
    while (1);
}

void putc(char ch, char attr, int row, int col) {
    short *video = (short*) 0xb8000;
    video[row*80+col] = (short) attr << 8 | ch;
}