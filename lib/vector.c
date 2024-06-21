#include <libspike/vector.h>
#include <stdio.h>
#include <stdlib.h>

void __attribute__((weak)) _init(void) {}
void __attribute__((weak)) _fini(void) {}

const vector_table_t isr_vector __attribute__((section(".isr_vector"))) = {
    .initial_sp_value = &_end_stack,
    .reset = reset_handler,
    .nmi = nmi_handler,
    .hard_fault = hard_fault_handler,
    .memory_manage_fault = memory_manage_fault_handler,
    .bus_fault = bus_fault_handler,
    .usage_fault = usage_fault_handler,
    .sv_call = sv_call_handler,
    .debug_monitor = debug_monitor_handler,
    .pend_sv = pend_sv_handler,
    .systick = systick_handler,
    .irq = VECTOR_IRQ_LIST
};

void reset_handler(void)
{
    volatile unsigned *flash_data = &_data_loadaddr;
    volatile unsigned *ram_data = &_start_data;

    /* Copy variables from flash. */
    while (ram_data < &_end_data)
        *ram_data++ = *flash_data++;

    volatile unsigned *bss = &_start_bss;

    /* Fill bss section with zero. */
    while (bss < &_end_bss)
        *bss++ = 0;

    /* Give coprocessors full access. */
    SCB->CPACR |= 0xf << 20;

    /* Run constructors. */
    __libc_init_array();
    
    /* Run the program. */
    int status = main();

    if (status != EXIT_SUCCESS)
        printf("\nProgram finished with non-zero return code: %d.\n", status);
    
    /* Run deconstructors. */
    __libc_fini_array();

    while (1);
}
