#ifndef IO_H
#define IO_H

void putd(int number, char attr, int row, int col);
void putc(char ch, char attr, int row, int col);
void puts(char *string, int length, char attr, int row, int col);
void clear();

int sputd(char *dest, int number);
int sputh(char *dest, int number);
int sputb(char *dest, int number);
int sputc(char *dest, char ch);
int sputs(char *dest, char *string, int length);

#endif