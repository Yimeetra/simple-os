#include "interrupts.h"
#include "timer.h"
#include "io.h"
#include "proc.h"

extern void irq0(void);

extern struct timer_channel channel0;

extern struct proc procs[MAX_PROCS];
extern struct proc *current_proc;


void put_context(struct context *context, int col) {
    puts("eip", 3, 0x0f, 1, col+0);
    puts("cs", 2, 0x0f, 2, col+0);
    puts("eflags", 6, 0x0f, 3, col+0);
    puts("edi", 3, 0x0f, 4, col+0);
    puts("esi", 3, 0x0f, 5, col+0);
    puts("ebp", 3, 0x0f, 6, col+0);
    puts("esp", 3, 0x0f, 7, col+0);
    puts("ebx", 3, 0x0f, 8, col+0);
    puts("edx", 3, 0x0f, 9, col+0);
    puts("ecx", 3, 0x0f, 10, col+0);
    puts("eax", 3, 0x0f, 11, col+0);

    putd(context->eip, 0x0f, 1, col+8);
    putd(context->cs, 0x0f, 2, col+8);
    putd(context->eflags, 0x0f, 3, col+8);
    putd(context->edi, 0x0f, 4, col+8);
    putd(context->esi, 0x0f, 5, col+8);
    putd(context->ebp, 0x0f, 6, col+8);
    putd(context->esp, 0x0f, 7, col+8);
    putd(context->ebx, 0x0f, 8, col+8);
    putd(context->edx, 0x0f, 9, col+8);
    putd(context->ecx, 0x0f, 10, col+8);
    putd(context->eax, 0x0f, 11, col+8);
}

void put_eip(char attr, int row, int col) {
    uint32_t eip;
    asm volatile (
        "call 1f\n"
        "1:\n"
        "pop %0\n"
        : "=r"(eip)
    );
    putd(eip, attr, row, col);
}

void irq0_handler(struct context *context) {
    struct context old;
    struct context new;
    channel0.counter++;
    putd((int)channel0.counter/channel0.frequency, 0x0f, 0, 0);

    for (int i = 0; i < MAX_PROCS; ++i) {
        switch (procs[i].state) {
        case PROC_FINISHED:
            puts("PROC_FINISHED", 14, 0x0f, 13+i, 0);
            break;
        case PROC_STOPPED:
            puts("PROC_STOPPED", 13, 0x0f, 13+i, 0);
            break;
        case PROC_RUNNING:
            puts("PROC_RUNNING", 13, 0x0f, 13+i, 0);
            break;
        default:
            break;
        }
    }

    if (current_proc != 0)
        current_proc->context = *context;
    current_proc = sched();

    outb(0x20, 0x20);

    if (current_proc != 0)
        switch_to(&current_proc->context);
}

void exepction_0_handler() {
    puts("Division Error", 15, 0x0f, 20, 0);
    while (1);
}

void exepction_1_handler() {
    puts("Debug", 6, 0x0f, 20, 0);
    while (1);
}

void exepction_2_handler() {
    puts("Non-maskable Interrupt", 23, 0x0f, 20, 0);
    while (1);
}

void exepction_3_handler() {
    puts("Breakpoint", 11, 0x0f, 20, 0);
    while (1);
}

void exepction_4_handler() {
    puts("Overflow", 9, 0x0f, 20, 0);
    while (1);
}

void exepction_5_handler() {
    puts("Bound Range Exceeded", 21, 0x0f, 20, 0);
    while (1);
}

void exepction_6_handler() {
    puts("Invalid Opcode", 15, 0x0f, 20, 0);
    while (1);
}

void exepction_7_handler() {
    puts("Device Not Available", 21, 0x0f, 20, 0);
    while (1);
}

void exepction_8_handler() {
    puts("Double Fault", 13, 0x0f, 20, 0);
    while (1);
}

void exepction_9_handler() {
    puts("Coprocessor Segment Overrun", 28, 0x0f, 20, 0);
    while (1);
}

void exepction_10_handler() {
    puts("Invalid TSS", 12, 0x0f, 20, 0);
    while (1);
}

void exepction_11_handler() {
    puts("Segment Not Present", 20, 0x0f, 20, 0);
    while (1);
}

void exepction_12_handler() {
    puts("Stack-Segment Fault", 20, 0x0f, 20, 0);
    while (1);
}

void exepction_13_handler() {
    puts("General Protection Fault", 25, 0x0f, 20, 0);
    while (1);
}

void exepction_14_handler() {
    puts("Page Fault", 11, 0x0f, 20, 0);
    while (1);
}

void exepction_15_handler() {
    puts("Reserved", 9, 0x0f, 20, 0);
    while (1);
}

void exepction_16_handler() {
    puts("x87 Floating-Point Exception", 29, 0x0f, 20, 0);
    while (1);
}

void exepction_17_handler() {
    puts("Alignment Check", 16, 0x0f, 20, 0);
    while (1);
}

void exepction_18_handler() {
    puts("Machine Check", 14, 0x0f, 20, 0);
    while (1);
}

void exepction_19_handler() {
    puts("SIMD Floating-Point Exception", 30, 0x0f, 20, 0);
    while (1);
}

void exepction_20_handler() {
    puts("Virtualization Exception", 25, 0x0f, 20, 0);
    while (1);
}

void exepction_21_handler() {
    puts("Control Protection Exception", 29, 0x0f, 20, 0);
    while (1);
}

void exepction_22_handler() {
    puts("Reserved", 9, 0x0f, 20, 0);
    while (1);
}

void exepction_28_handler() {
    puts("Hypervisor Injection Exception", 31, 0x0f, 20, 0);
    while (1);
}

void exepction_29_handler() {
    puts("VMM Communication Exception", 28, 0x0f, 20, 0);
    while (1);
}

void exepction_30_handler() {
    puts("Security Exception", 19, 0x0f, 20, 0);
    while (1);
}

void exepction_31_handler() {
    puts("Reserved", 9, 0x0f, 20, 0);
    while (1);
}

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

    idt_add_gate(0x20, (uintptr_t) irq0, 0x0008, 0x8E);

    idt_add_gate(0, (uintptr_t) exepction_0_handler, 0x0008, 0x8E);
    idt_add_gate(1, (uintptr_t) exepction_1_handler, 0x0008, 0x8E);
    idt_add_gate(2, (uintptr_t) exepction_2_handler, 0x0008, 0x8E);
    idt_add_gate(3, (uintptr_t) exepction_3_handler, 0x0008, 0x8E);
    idt_add_gate(4, (uintptr_t) exepction_4_handler, 0x0008, 0x8E);
    idt_add_gate(5, (uintptr_t) exepction_5_handler, 0x0008, 0x8E);
    idt_add_gate(6, (uintptr_t) exepction_6_handler, 0x0008, 0x8E);
    idt_add_gate(7, (uintptr_t) exepction_7_handler, 0x0008, 0x8E);
    idt_add_gate(8, (uintptr_t) exepction_8_handler, 0x0008, 0x8E);
    idt_add_gate(9, (uintptr_t) exepction_9_handler, 0x0008, 0x8E);
    idt_add_gate(10, (uintptr_t) exepction_10_handler, 0x0008, 0x8E);
    idt_add_gate(11, (uintptr_t) exepction_11_handler, 0x0008, 0x8E);
    idt_add_gate(12, (uintptr_t) exepction_12_handler, 0x0008, 0x8E);
    idt_add_gate(13, (uintptr_t) exepction_13_handler, 0x0008, 0x8E);
    idt_add_gate(14, (uintptr_t) exepction_14_handler, 0x0008, 0x8E);
    idt_add_gate(15, (uintptr_t) exepction_15_handler, 0x0008, 0x8E);
    idt_add_gate(16, (uintptr_t) exepction_16_handler, 0x0008, 0x8E);
    idt_add_gate(17, (uintptr_t) exepction_17_handler, 0x0008, 0x8E);
    idt_add_gate(18, (uintptr_t) exepction_18_handler, 0x0008, 0x8E);
    idt_add_gate(19, (uintptr_t) exepction_19_handler, 0x0008, 0x8E);
    idt_add_gate(20, (uintptr_t) exepction_20_handler, 0x0008, 0x8E);
    idt_add_gate(21, (uintptr_t) exepction_21_handler, 0x0008, 0x8E);
    idt_add_gate(22, (uintptr_t) exepction_22_handler, 0x0008, 0x8E);
    idt_add_gate(28, (uintptr_t) exepction_28_handler, 0x0008, 0x8E);
    idt_add_gate(29, (uintptr_t) exepction_29_handler, 0x0008, 0x8E);
    idt_add_gate(30, (uintptr_t) exepction_30_handler, 0x0008, 0x8E);
    idt_add_gate(31, (uintptr_t) exepction_31_handler, 0x0008, 0x8E);
}