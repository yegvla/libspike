ENTRY(reset_handler)

MEMORY
{
    FLASH (rx): ORIGIN = 0x08000000, LENGTH = 1M
    RAM (rwx): ORIGIN = 0x20000000, LENGTH = 128K 
    AXISRAM (rwx): ORIGIN = 0x24000000, LENGTH = 128K
    SRAM1 (rwx): ORIGIN = 0x30000000, LENGTH = 16K
    SRAM2 (rwx): ORIGIN = 0x30004000, LENGTH = 16K
    SRAM4 (rwx): ORIGIN = 0x38000000, LENGTH = 16K
}

_end_stack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } >FLASH

    .text :
    {
        . = ALIGN(4);

        *(.text*)
        *(.rodata*)

        . = ALIGN(4);
        _end_text = .;
    } >FLASH

    .preinit_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } >FLASH

    .init_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);
    } >FLASH

    .fini_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >FLASH

    .data :
    {
        . = ALIGN(4);
        _start_data = .;

        *(.data*)

        . = ALIGN(4);
        _end_data = .;
    } >RAM AT> FLASH

    _data_loadaddr = LOADADDR(.data);

    .bss :
    {
        . = ALIGN(4);
        _start_bss = .;
        __bss_start__ = _start_bss;
        
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _end_bss = .;
        __bss_end__ = _end_bss;
    } >RAM

    /DISCARD/ : { *(.eh_frame) }
}

