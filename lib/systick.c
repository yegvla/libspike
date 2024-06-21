#include "libspike/nvic.h"
#include "stm32h723xx.h"
#include "stm32h7xx.h"
#include <libspike/systick.h>

inline void systick_set_clock_source(enum systick_clock_source src)
{
    MODIFY_REG(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk, src);
}

inline void systick_set_reload(uint32_t reload)
{
    SysTick->LOAD = reload;
}

inline void systick_set_counter(uint32_t cnt)
{
    SysTick->VAL = cnt;
}

inline void systick_enable_interrupt(void)
{
    nvic_set_priority(SysTick_IRQn, 15);
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

inline void systick_disable_interrupt(void)
{
    SysTick->CTRL &= SysTick_CTRL_TICKINT_Msk;
}

inline void systick_start(void)
{
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

inline void systick_disable(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

