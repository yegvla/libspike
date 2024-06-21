#include "libspike/rcc.h"
#include <libspike/syscfg.h>
#include <stm32h7xx.h>

void syscfg_enable(void)
{
    rcc_enable_clock(RCC_SYSCFG);
}

bool syscfg_cpu_freq_boost(void)
{
    return SYSCFG->UR18 & SYSCFG_UR18_CPU_FREQ_BOOST;
}
