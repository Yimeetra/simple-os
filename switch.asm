global switch_to

;struct context {
;    uint32_t edi;
;    uint32_t esi;
;    uint32_t ebp;
;    uint32_t old_esp;
;    uint32_t ebx;
;    uint32_t edx;
;    uint32_t ecx;
;    uint32_t eax;
;    uint32_t eip;
;    uint32_t cs;
;    uint32_t eflags;
;}

; void switch_to(context *new);
switch_to:
    mov eax, [esp + 4]

    mov esp, [eax + 12]
    sub esp, 32

    mov ebx, [eax +  0]
    mov [esp +  0], ebx
    
    mov ebx, [eax +  4]
    mov [esp +  4], ebx
    
    mov ebx, [eax +  8]
    mov [esp +  8], ebx
    
    mov ebx, [eax + 12]
    mov [esp + 12], ebx
    
    mov ebx, [eax + 16]
    mov [esp + 16], ebx
    
    mov ebx, [eax + 20]
    mov [esp + 20], ebx
    
    mov ebx, [eax + 24]
    mov [esp + 24], ebx
    
    mov ebx, [eax + 28]
    mov [esp + 28], ebx
    
    mov ebx, [eax + 32]
    mov [esp + 32], ebx
    
    mov ebx, [eax + 36]
    mov [esp + 36], ebx
    
    mov ebx, [eax + 40]
    mov [esp + 40], ebx
    
    popa 
    
    iretd