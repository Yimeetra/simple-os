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