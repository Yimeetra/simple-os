#include "interrupts.h"
#include "timer.h"
#include "io.h"
#include "proc.h"
#include "string.h"

extern void irq0(void);
extern void irq1(void);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

char *exception_name[32] = {
    "Division Error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

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

void irq0_handler(struct context *context) {
    channel0.counter++;
    putd((int)channel0.counter/channel0.frequency, 0x0f, 0, 0);

    //for (int i = 0; i < MAX_PROCS; ++i) {
    //    switch (procs[i].state) {
    //    case PROC_FINISHED:
    //        puts("PROC_FINISHED", 14, 0x0f, 13+i, 0);
    //        break;
    //    case PROC_STOPPED:
    //        puts("PROC_STOPPED", 13, 0x0f, 13+i, 0);
    //        break;
    //    case PROC_RUNNING:
    //        puts("PROC_RUNNING", 13, 0x0f, 13+i, 0);
    //        break;
    //    default:
    //        break;
    //    }
    //}

    if (current_proc != 0)
        current_proc->context = *context;
    current_proc = sched();

    outb(0x20, 0x20);

    if (current_proc != 0)
        switch_to(&current_proc->context);
}

void irq1_handler() {
    outb(0x20, 0x20);
}

void exception_handler(int exception, int error_code) {
    puts(exception_name[exception], strlen(exception_name[exception]), 0x0f, 0, 0);
    putd(error_code, 0x0f, 0, strlen(exception_name[exception]) + 1);
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

    idt_add_gate(32, (uintptr_t) irq0, 0x0008, 0x8E);
    idt_add_gate(33, (uintptr_t) irq1, 0x0008, 0x8E);
    
    idt_add_gate(0,  (uintptr_t) isr0,  0x08, 0x8E);
    idt_add_gate(1,  (uintptr_t) isr1,  0x08, 0x8E);
    idt_add_gate(2,  (uintptr_t) isr2,  0x08, 0x8E);
    idt_add_gate(3,  (uintptr_t) isr3,  0x08, 0x8E);
    idt_add_gate(4,  (uintptr_t) isr4,  0x08, 0x8E);
    idt_add_gate(5,  (uintptr_t) isr5,  0x08, 0x8E);
    idt_add_gate(6,  (uintptr_t) isr6,  0x08, 0x8E);
    idt_add_gate(7,  (uintptr_t) isr7,  0x08, 0x8E);
    idt_add_gate(8,  (uintptr_t) isr8,  0x08, 0x8E);
    idt_add_gate(9,  (uintptr_t) isr9,  0x08, 0x8E);
    idt_add_gate(10, (uintptr_t) isr10, 0x08, 0x8E);
    idt_add_gate(11, (uintptr_t) isr11, 0x08, 0x8E);
    idt_add_gate(12, (uintptr_t) isr12, 0x08, 0x8E);
    idt_add_gate(13, (uintptr_t) isr13, 0x08, 0x8E);
    idt_add_gate(14, (uintptr_t) isr14, 0x08, 0x8E);
    idt_add_gate(15, (uintptr_t) isr15, 0x08, 0x8E);
    idt_add_gate(16, (uintptr_t) isr16, 0x08, 0x8E);
    idt_add_gate(17, (uintptr_t) isr17, 0x08, 0x8E);
    idt_add_gate(18, (uintptr_t) isr18, 0x08, 0x8E);
    idt_add_gate(19, (uintptr_t) isr19, 0x08, 0x8E);
    idt_add_gate(20, (uintptr_t) isr20, 0x08, 0x8E);
    idt_add_gate(21, (uintptr_t) isr21, 0x08, 0x8E);
    idt_add_gate(22, (uintptr_t) isr22, 0x08, 0x8E);
    idt_add_gate(23, (uintptr_t) isr23, 0x08, 0x8E);
    idt_add_gate(24, (uintptr_t) isr24, 0x08, 0x8E);
    idt_add_gate(25, (uintptr_t) isr25, 0x08, 0x8E);
    idt_add_gate(26, (uintptr_t) isr26, 0x08, 0x8E);
    idt_add_gate(27, (uintptr_t) isr27, 0x08, 0x8E);
    idt_add_gate(28, (uintptr_t) isr28, 0x08, 0x8E);
    idt_add_gate(29, (uintptr_t) isr29, 0x08, 0x8E);
    idt_add_gate(30, (uintptr_t) isr30, 0x08, 0x8E);
    idt_add_gate(31, (uintptr_t) isr31, 0x08, 0x8E);
}