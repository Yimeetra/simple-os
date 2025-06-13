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