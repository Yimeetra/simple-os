OUTPUT_ARCH(i386)
OUTPUT_FORMAT(binary)

SECTIONS 
{
    . = 0x10000;
    .text : 
    {
        *(.text);
    }
    .data :
    {
        *(.data .data.*)
    }
}