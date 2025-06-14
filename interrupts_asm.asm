global irq0
extern irq0_handler
irq0:
    pushad
    mov eax, esp
    push eax
    call irq0_handler
    add esp, 4
    popad
    iretd

global irq1
extern irq1_handler
irq1:
    call irq1_handler
    iretd

extern exception_handler

global isr0
isr0:
    pushad
    push 0
    push 0
    call exception_handler
    add esp, 4
    popad
    iretd

global isr1
isr1:
    pushad
    push 0
    push 1
    call exception_handler
    add esp, 4
    popad
    iretd

global isr2
isr2:
    pushad
    push 0
    push 2
    call exception_handler
    add esp, 4
    popad
    iretd

global isr3
isr3:
    pushad
    push 0
    push 3
    call exception_handler
    add esp, 4
    popad
    iretd

global isr4
isr4:
    pushad
    push 0
    push 4
    call exception_handler
    add esp, 4
    popad
    iretd

global isr5
isr5:
    pushad
    push 0
    push 5
    call exception_handler
    add esp, 4
    popad
    iretd

global isr6
isr6:
    pushad
    push 0
    push 6
    call exception_handler
    add esp, 4
    popad
    iretd

global isr7
isr7:
    pushad
    push 0
    push 7
    call exception_handler
    add esp, 4
    popad
    iretd

global isr8
isr8:
    pushad
    push 0
    push 8
    call exception_handler
    add esp, 4
    popad
    iretd

global isr9
isr9:
    pushad
    push 0
    push 9
    call exception_handler
    add esp, 4
    popad
    iretd

global isr10
isr10:
    pushad
    push DWORD [esp + 36]
    push 10
    call exception_handler
    add esp, 4
    popad
    iretd

global isr11
isr11:
    pushad
    push DWORD [esp + 36]
    push 11
    call exception_handler
    add esp, 4
    popad
    iretd

global isr12
isr12:
    pushad
    push DWORD [esp + 36]
    push 12
    call exception_handler
    add esp, 4
    popad
    iretd

global isr13
isr13:
    pushad
    push DWORD [esp + 36]
    push 13
    call exception_handler
    add esp, 4
    popad
    iretd

global isr14
isr14:
    pushad
    push DWORD [esp + 36]
    push 14
    call exception_handler
    add esp, 4
    popad
    iretd

global isr15
isr15:
    pushad
    push 0
    push 15
    call exception_handler
    add esp, 4
    popad
    iretd

global isr16
isr16:
    pushad
    push 0
    push 16
    call exception_handler
    add esp, 4
    popad
    iretd

global isr17
isr17:
    pushad
    push DWORD [esp + 36]
    push 17
    call exception_handler
    add esp, 4
    popad
    iretd

global isr18
isr18:
    pushad
    push 0
    push 18
    call exception_handler
    add esp, 4
    popad
    iretd

global isr19
isr19:
    pushad
    push 0
    push 19
    call exception_handler
    add esp, 4
    popad
    iretd

global isr20
isr20:
    pushad
    push 0
    push 20
    call exception_handler
    add esp, 4
    popad
    iretd

global isr21
isr21:
    pushad
    push DWORD [esp + 36]
    push 21
    call exception_handler
    add esp, 4
    popad
    iretd

global isr22
isr22:
    pushad
    push 0
    push 22
    call exception_handler
    add esp, 4
    popad
    iretd

global isr23
isr23:
    pushad
    push 0
    push 23
    call exception_handler
    add esp, 4
    popad
    iretd

global isr24
isr24:
    pushad
    push 0
    push 24
    call exception_handler
    add esp, 4
    popad
    iretd

global isr25
isr25:
    pushad
    push 0
    push 25
    call exception_handler
    add esp, 4
    popad
    iretd

global isr26
isr26:
    pushad
    push 0
    push 26
    call exception_handler
    add esp, 4
    popad
    iretd

global isr27
isr27:
    pushad
    push 0
    push 27
    call exception_handler
    add esp, 4
    popad
    iretd

global isr28
isr28:
    pushad
    push 0
    push 28
    call exception_handler
    add esp, 4
    popad
    iretd

global isr29
isr29:
    pushad
    push DWORD [esp + 36]
    push 29
    call exception_handler
    add esp, 4
    popad
    iretd

global isr30
isr30:
    pushad
    push DWORD [esp + 36]
    push 30
    call exception_handler
    add esp, 4
    popad
    iretd

global isr31
isr31:
    pushad
    push 0
    push 31
    call exception_handler
    add esp, 4
    popad
    iretd