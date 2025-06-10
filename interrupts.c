#include "interrupts.h"
#include "timer.h"

extern void irq0(void);

void interrupts_init() {
    idt_init();

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    
    outb(0x21, 0x04);
    outb(0xA1, 0x02);

    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    idt_add_gate(0x20, irq0, 0x0008, 0x8E);
}

extern struct timer_channel channel0;

void irq0_handler() {
    channel0.counter++;
    putc('0'+(int)channel0.counter/channel0.frequency, 0x0f, 0, 0);

    outb(0x20, 0x20);
}