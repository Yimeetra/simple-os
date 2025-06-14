#include "interrupts.h"
#include "inline_asm.h"
#include "timer.h"
#include "io.h"
#include "proc.h"
#include "gdt.h"

char stdout[1024*4] = "";
int len = 0;

void proc1() {
    while (1) {
        int col = 0;
        int row = 15;
        for (int i = 0; i < len; ++i) {
            switch (stdout[i]) {
            case '\n':
                row++;
                break;

            case '\r':
                col = 0;
                break;
        
            
            default:
                putc(stdout[i], 0x0f, row, col);
                col++;
                break;
            }
        
        }
    }
}

void main() {
    gdt_init();
    interrupts_init();
    pit_set_frequency(50);
    procs_init();

    clear();

    create_proc(proc1);


    __asm__ volatile("sti");

    while (1);
}