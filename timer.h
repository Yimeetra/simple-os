#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define BASE_FREQUENCY 1193181

struct timer_channel {
    uint32_t counter;
    uint32_t frequency;
};

extern struct timer_channel channel0;

void pit_set_frequency(uint32_t frequency);
void sleep(float seconds);

#endif