[bits 16]
[org 0x7C00]

boot:
.reset:
    mov ah, 00h
    int 13h
.read:
    mov ax, 0x1000
    mov es, ax
    mov bx, 0x0

    mov ah, 02h
    mov al, 40h
    mov ch, 00h
    mov cl, 02h
    mov dh, 00h
    mov dl, 00h
    int 13h

    jc .read

    cli
    lgdt [GDT_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp CODESEG:start_protected_mode

[bits 32]
start_protected_mode:
    mov   ax, DATASEG
    mov   ds, ax
    mov   es, ax
    mov   fs, ax
    mov   gs, ax
    mov   ss, ax

    mov ebp, 0x90000
    mov esp, ebp

    jmp 0x10000

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start

GDT_start:

null_descriptor:
    dd 0
    dd 0

code_descriptor:
    dw 0xffff
    dw 0
    db 0
    db 10011010b
    db 11001111b
    db 0

data_descriptor:
    dw 0xffff
    dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0

GDT_end:

CODESEG equ code_descriptor-GDT_start
DATASEG equ data_descriptor-GDT_start

times 510-($-$$) db 0
dw 0xAA55  