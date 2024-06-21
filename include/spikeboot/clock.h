#ifndef SPIKEBOOT_CLOCK_H
#define SPIKEBOOT_CLOCK_H

#include <stdint.h>
#include <stdbool.h>
#include <stdatomic.h>

/* tick_t describes a "little" amount of ticks without a specialized usecase.
 *
 * instant_t describes a instant, it can be in the future or in the past, it is
 * 64-bit wide because the internal tick counter is 58-bit wide.  Using the
 * fastest clock-setting the 32-bit boundary would be surpassed in about 2
 * minutes.
 *
 * long_tick_t is like tick_t but it can hold a larger amount of ticks. */
typedef uint32_t tick_t;
typedef uint64_t instant_t;
typedef uint64_t long_tick_t;

/* This variable is clock-setting dependent, it specifies the frequency of the
 * internal systick timer.  When you change the clock for systick, then you will
 * need to update this value. */
extern tick_t _ticks_per_second;

/* Counts systick overflows 1 = 2^24-1 ticks = 16777215. */
extern volatile atomic_uint_fast32_t _tick_overflows_since_reset;

/* Macros for getting the time since reset. */
#define CLOCK_TICKS_SINCE_RESET (((instant_t)                           \
                                  _tick_overflows_since_reset << 24)    \
                                 | (16777215 - SysTick->VAL))

#define CLOCK_MINS_SINCE_RESET  (CLOCK_TICKS_SINCE_RESET /      \
                                 (_ticks_per_second * 60))
#define CLOCK_SECS_SINCE_RESET  (CLOCK_TICKS_SINCE_RESET /      \
                                 _ticks_per_second)
#define CLOCK_MS_SINCE_RESET    (CLOCK_TICKS_SINCE_RESET /      \
                                 (_ticks_per_second / 1000))
#define CLOCK_US_SINCE_RESET    (CLOCK_TICKS_SINCE_RESET /      \
                                 (_ticks_per_second / 1000000))

/* Tick conversion macros. */
#define CLOCK_US(US)      (US * (_ticks_per_second / 1000000))
#define CLOCK_MS(MS)      (MS * (_ticks_per_second / 1000))
#define CLOCK_SECS(SECS)  (SECS * (_ticks_per_second))
#define CLOCK_MIN(MINS)   (MINS * (_ticks_per_second * 60))
#define CLOCK_HOUR(HOURS) (HOURS * (_ticks_per_second * 3600))

/* Starts the clock. */
void clock_start(void);

/* Resets the clock, be very cautios with this method.  Any already defined
 * instants will be in a much futher future. */
void clock_reset(void);

/* Will halt execution (busy-wait) until the specified ticks have passed. */
void clock_block_for(tick_t ticks);
void clock_block_forl(long_tick_t ticks);

/* Will return the current time + the specified ticks and return that value in
 * ticks.  Useful for waiting for some action to complete:
 *
 * tick_t timeout = clock_after(CLOCK_MS(100));
 * while (!clock_reached(timeout)) {
 *      foo();
 * } */
instant_t clock_after(tick_t ticks);
instant_t clock_afterl(long_tick_t ticks);

/* Returns true when the specified instant was reached at any point in time. */
bool clock_reached(instant_t instant);

/* Needs to be called with the new frequency of HCLK in case it was updated. */
void clock_update_tick_freq(uint32_t freq);

#endif /* SPIKEBOOT_CLOCK_H */
