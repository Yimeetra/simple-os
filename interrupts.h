#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "idt.h"
#include "inline_asm.h"

void interrupts_init();

void isr0_handler();

#endif