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
    mov al, 01h
    mov ch, 00h
    mov cl, 02h
    mov dh, 00h
    mov dl, 00h
    int 13h

    jc .read

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x2000

    jmp 0x1000:0000

times 510-($-$$) db 0
dw 0xAA55  