#include "idt.h"

struct idt_entry idt[256] = {0};
struct idt_descriptor idt_desc;

void idt_init() {
    idt_desc.size = sizeof(idt) - 1;
    idt_desc.offset = (uintptr_t) &idt;

    __asm__ volatile("lidtl (%0)" : : "r" (&idt_desc));
}

void idt_add_gate(uint8_t index, uintptr_t gate, uint16_t segment, uint8_t attributes) {
    idt[index].offset = gate & 0xFFFF;
    idt[index].segment = segment;
    idt[index].reserved = 0;
    idt[index].attributes = attributes;
    idt[index].offset_high = (gate >> 16) & 0xFFFF;
}