#include "timer.h"
#include "inline_asm.h"

struct timer_channel channel0 = {0};

void pit_set_frequency(uint32_t frequency) {
    channel0.frequency = frequency;
    outb(0x43, 0x36);
    outb(0x40, (BASE_FREQUENCY/frequency));
    outb(0x40, (BASE_FREQUENCY/frequency) >> 8);
}
