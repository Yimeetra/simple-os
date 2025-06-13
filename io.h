#ifndef IO_H
#define IO_H

void putd(int number, char attr, int row, int col);
void putc(char ch, char attr, int row, int col);
void puts(char *string, int length, char attr, int row, int col);
void clear();

#endif