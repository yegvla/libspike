#ifndef LIBSPIKE_SYSTICK_H
#define LIBSPIKE_SYSTICK_H

#include <stdint.h>
#include <stm32h7xx.h>

enum systick_clock_source {
    /* Internal */
    SYSTICK_CLOCK_HCLK = 1 << SysTick_CTRL_CLKSOURCE_Pos,
    /* External */
    SYSTICK_CLOCK_HCLK_DIV8  = 0 << SysTick_CTRL_CLKSOURCE_Pos
};

void systick_set_clock_source(enum systick_clock_source src);
void systick_set_reload(uint32_t reload);
void systick_set_counter(uint32_t cnt);
void systick_enable_interrupt(void);
void systick_disable_interrupt(void);
void systick_start(void);
void systick_disable(void);

#endif /* LIBSPIKE_SYSTICK_H */
