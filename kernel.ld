OUTPUT_ARCH(i386)
ENTRY(main);

SECTIONS 
{
    . = 0x10000;
    
    .text : {
        KEEP(*(.text.main))
        *(.text .text.*)
    }
    .data : { *(.data .data.*) }
    .bss  : { *(.bss .bss.*) }

    /DISCARD/ :
    {
        *(.comment)
    }
}