#include "proc.h"
#include "io.h"

struct proc procs[MAX_PROCS] = {0};
struct proc *current_proc = 0;
uint32_t procs_amount = 0;

void _proc_exit_callback() {
    while (1)
        current_proc->state = PROC_FINISHED;
}

void init_proc_stack(struct proc *proc, void (*entry)(), uint32_t *stack_top) {
    proc->context.edi = 0;
    proc->context.esi = 0;
    proc->context.ebp = stack_top;
    proc->context.esp = stack_top-3;
    proc->context.ebx = 0;
    proc->context.edx = 0;
    proc->context.ecx = 0;
    proc->context.eax = 0;
    proc->context.eip = entry;
    proc->context.cs = 0x0008;
    proc->context.eflags = 530;
    
    *stack_top = (uint32_t) _proc_exit_callback;
}

void procs_init() {
    for (int i = 0; i < MAX_PROCS; ++i) {
        procs[i].pid = i;
        procs[i].state = PROC_FINISHED;
    }
}

int32_t create_proc(void (*entry)()) {
    for (int i = 0; i < MAX_PROCS; ++i) {
        if (procs[i].state == PROC_FINISHED) {
            struct proc *proc = &procs[i];
            init_proc_stack(proc, entry, PROCS_SPACE_START + i*(PROC_STACK_SIZE + PROC_PADDING));
            proc->pid = i;
            proc->state = PROC_STOPPED;
            return i;
        }
    }
    return -1;
}

struct proc *sched() {
    int start = 0;
    if (current_proc->state == PROC_RUNNING)
        current_proc->state = PROC_STOPPED;
        
    if (current_proc != 0) {
        if (current_proc->pid != MAX_PROCS - 1)
            start = current_proc->pid+1;
    }

    for (int i = start; i < MAX_PROCS; ++i) {
        if (procs[i].state != PROC_FINISHED) {
            procs[i].state = PROC_RUNNING;
            return &procs[i];
        }
    }
    return 0;
}