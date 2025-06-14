#include "gdt.h"

struct gdt_descriptor gdt_descriptor;
struct gdt_entry *gdt;

void gdt_init() {
    gdt[0].limit           = 0x0000;
    gdt[0].base_low        = 0x0000;
    gdt[0].base_mid        = 0x00;
    gdt[0].access_byte     = 0x00;
    gdt[0].flags_and_limit = 0x00;
    gdt[0].base_high       = 0x00;

    gdt[1].limit           = 0xffff;
    gdt[1].base_low        = 0x0000;
    gdt[1].base_mid        = 0x00;
    gdt[1].access_byte     = 0x9A;
    gdt[1].flags_and_limit = 0xcf;
    gdt[1].base_high       = 0x00;

    gdt[2].limit           = 0xffff;
    gdt[2].base_low        = 0x0000;
    gdt[2].base_mid        = 0x00;
    gdt[2].access_byte     = 0x92;
    gdt[2].flags_and_limit = 0xcf;
    gdt[2].base_high       = 0x00;

    gdt_descriptor.size = 3 * sizeof(struct gdt_entry) - 1;
    gdt_descriptor.offset = (uint32_t)gdt;

    asm volatile("lgdt (%0)" :: "r" (&gdt_descriptor));

    asm volatile (
        "jmp $0x08, $.1\n"
        ".1:\n"
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        :
        :
        : "memory", "ax"
    );
}

void gdt_add_entry(struct gdt_entry entry) {
    int len = (gdt_descriptor.size + 1) / sizeof(struct gdt_entry);
    gdt[len] = entry;
    gdt_descriptor.size = (len + 1) * sizeof(struct gdt_entry) - 1;
}