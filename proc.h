#ifndef PROC_H
#define PROC_H

#include <stdint.h>

#define MAX_PROCS 10
#define PROC_STACK_SIZE 0x1000
#define PROC_PADDING 0x1000
#define PROCS_SPACE_START 0x20000

struct context {
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
};

enum proc_state {
    PROC_STOPPED,
    PROC_RUNNING,
    PROC_FINISHED
};

struct proc {
    struct context context; 
    uint32_t pid;
    enum proc_state state;
};

extern struct proc procs[MAX_PROCS];
extern struct proc *current_proc;
extern uint32_t procs_amount;


extern void switch_to(struct context *new);
int32_t create_proc(void (*entry)());
struct proc *sched();
void procs_init();

#endif