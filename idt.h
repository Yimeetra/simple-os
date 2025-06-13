#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_descriptor {
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

struct idt_entry {
    uint16_t offset;
    uint16_t segment;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t offset_high;
} __attribute__((packed));

extern void idt_init();
extern void idt_add_gate(uint8_t index, uintptr_t gate, uint16_t segment, uint8_t attributes);

#endif