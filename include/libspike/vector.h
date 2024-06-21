#ifndef LIBSPIKE_VECTOR_H
#define LIBSPIKE_VECTOR_H

#include <stm32h7xx.h>
#include "irq.h"

extern unsigned _end_text, _start_data, _end_data, _start_bss, _end_bss, _end_stack, _data_loadaddr;

typedef void (*vector_table_entry_t)(void);

void blocking_handler(void);
void nop_handler(void);

void reset_handler(void);
void nmi_handler(void);
void hard_fault_handler(void);
void memory_manage_fault_handler(void);
void bus_fault_handler(void);
void usage_fault_handler(void);
void sv_call_handler(void);
void debug_monitor_handler(void);
void pend_sv_handler(void);
void systick_handler(void);

int main(void);
void _init(void);
void _fini(void);
void __libc_init_array(void);
void __libc_fini_array(void);

typedef struct {
    unsigned *initial_sp_value;
    vector_table_entry_t reset;
    vector_table_entry_t nmi;
    vector_table_entry_t hard_fault;
    vector_table_entry_t memory_manage_fault;
    vector_table_entry_t bus_fault;
    vector_table_entry_t usage_fault;
    vector_table_entry_t reserved_x001c[4];
    vector_table_entry_t sv_call;
    vector_table_entry_t debug_monitor;
    vector_table_entry_t reserved_x0034;
    vector_table_entry_t pend_sv;
    vector_table_entry_t systick;
    vector_table_entry_t irq[VECTOR_IRQ_COUNT];
} vector_table_t;

#endif  /* LIBSPIKE_VECTOR_H */
