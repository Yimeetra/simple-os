#include "interrupts.h"
#include "inline_asm.h"
#include "timer.h"
#include "io.h"
#include "proc.h"


void proc1() {
    for (int i = 0;; ++i) {
        putd(i, 0x0f, 0, 8);
        sleep(.1);
    }
}

void proc2() {
    for (int i = 0; i < 10; ++i) {
        putd(i, 0x0f, 0, 16);
        sleep(.1);
    }
}

void main() {
    interrupts_init();
    pit_set_frequency(100);
    procs_init();

    create_proc(proc1);
    create_proc(proc2);

    clear();

    __asm__ volatile("sti");

    while (1);
}