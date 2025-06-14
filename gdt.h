#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct gdt_descriptor {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

struct gdt_entry {
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access_byte;
    uint8_t flags_and_limit; // | 7 flags 4 | 3 limit 0 |
    uint8_t base_high;
} __attribute__((packed));

extern struct gdt_descriptor gdt_descriptor;
extern struct gdt_entry *gdt;

void gdt_init();
void gdt_add_entry(struct gdt_entry entry);

#endif