#include <libspike/vector.h>
#include <libspike/systick.h>
#include <spikeboot/clock.h>

/* Default HCLK is 64MHz, because we use DIV8 that makes 8MHz. */
tick_t _ticks_per_second = 8000000;
volatile atomic_uint_fast32_t _tick_overflows_since_reset = 0;

void systick_handler(void)
{
    atomic_fetch_add(&_tick_overflows_since_reset, 1);
}

void clock_update_tick_freq(uint32_t freq)
{
    _ticks_per_second = freq;
}

void clock_start(void)
{
    /* DIV8 is still plenty fast. */
    systick_set_clock_source(SYSTICK_CLOCK_HCLK_DIV8);
    systick_set_reload(16777215); /* 2^24-1 (The timer limit) */
    systick_enable_interrupt();
    systick_start();
}

void clock_reset(void)
{
    SysTick->VAL  = 0x00ffffff; /* 24-bit limit, the counter is
                                 * actually decrementing. */
    _tick_overflows_since_reset = 0;
}

void clock_block_for(tick_t ticks)
{
    instant_t wait_until = CLOCK_TICKS_SINCE_RESET + ticks;
    while (wait_until > CLOCK_TICKS_SINCE_RESET);
}

void clock_block_forl(long_tick_t ticks)
{
    instant_t wait_until = CLOCK_TICKS_SINCE_RESET + ticks;
    while (wait_until > CLOCK_TICKS_SINCE_RESET);
}

instant_t clock_after(tick_t ticks)
{
    return CLOCK_TICKS_SINCE_RESET + ticks;
}

instant_t clock_afterl(long_tick_t ticks)
{
    return CLOCK_TICKS_SINCE_RESET + ticks;
}

bool clock_reached(instant_t instant)
{
    return CLOCK_TICKS_SINCE_RESET >= instant;
}
