#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "idt.h"
#include "inline_asm.h"

extern char *exception_name[32];

void interrupts_init();

#endif