#include <libspike/nvic.h>
#include <libspike/syscfg.h>
#include <libspike/pwr.h>
#include <libspike/rcc.h>
#include <libspike/gpio.h>
#include <spikeboot/main.h>
#include <spikeboot/clock.h>
#include <spikeboot/com.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    /* Four priority bits and no subpriorities. */
    nvic_set_priority_grouping(NVIC_PRIORITY_GROUP4);
    __enable_irq();

    /* Start the clock. */
    clock_start();

    /* Clock syscfg for access to registers. */
    syscfg_enable();
    if (!syscfg_cpu_freq_boost()) {
        printf("ERROR: CPU_FREQ_BOOST is not enabled!\n"
               "The clock setting wont work without it enabled.\n"
               "Please make sure everything is flashed correctly.\n");
        return BOOTLOADER_EXIT_CPU_FREQ;
    }

    /* Configure power. */
    pwr_ldo_supply();
    pwr_voltage_scaling(PWR_VOLTAGE_SCALE0);

    /* Configure clocks. */
    rcc_configure_clocks(
        (struct rcc_clock_config) {
            .active_osci = RCC_OSCILLATOR_HSE,
            .bypass_hse = true,
            .sysclk_src = RCC_SYSCLK_SOURCE_PLL,
            .pll_src = RCC_PLL_SOURCE_HSE,
            .pll1 = {
                .divm = 1,
                .divn = 68,
                .divp = 1,
                .divq = 2,
                .divr = 2,
                .fracn = 6144,
                .rge = RCC_VCI_RANGE_8_16_MHZ,
                .vcosel = RCC_VCO_WIDE
            },
            .pll2 = {
                .divm = 1,
                .divn = 32,
                .divp = 2,
                .divq = 2,
                .divr = 2,
                .fracn = 0,
                .rge = RCC_VCI_RANGE_8_16_MHZ,
                .vcosel = RCC_VCO_WIDE
            },
            .pll3 = {
                .divm = 1,
                .divn = 24,
                .divp = 2,
                .divq = 4,
                .divr = 12,
                .fracn = 0,
                .rge = RCC_VCI_RANGE_8_16_MHZ,
                .vcosel = RCC_VCO_WIDE
            },
            .flash_latency = FLASH_LATENCY3,
            .cpre = RCC_CPRE_DIV1,
            .hpre = RCC_HPRE_DIV2,
            .ppre3 = RCC_PPRE3_DIV2,
            .ppre1 = RCC_PPRE1_DIV2,
            .ppre2 = RCC_PPRE2_DIV2,
            .ppre4 = RCC_PPRE4_DIV2
        }
    );

    /* Update clock.  550MHz / 8 = 68.75MHz. */
    clock_update_tick_freq(68750000);
    clock_reset();

    /* com_init(); */

    rcc_enable_clock(RCC_GPIOE);
    /* rcc_enable_clock(RCC_GPIOC); */
    /* gpio_mode(GPIOC, GPIO3, GPIO_MODE_AF); */
    gpio_mode(GPIOE, GPIO1, GPIO_MODE_OUTPUT);
    gpio_speed(GPIOE, GPIO1, GPIO_SPEED_LOW);

    /* rcc_enable_clock(RCC_TIM1); */
    /* timer_enable(TIM1); */
    /* timer_pwm(TIMER_PWM_MODE1); */
    /* timer_prescaler(TIM1, 1); */
    /* timer_mode(TIM1, TIM_COUNT_UP); */
    /* timer_auto_reload_preload(true); */
    /* timer_output_compare_preload(true); */
    /* timer_start(TIM1); */

    printf("Hello World!\n");

    while (true) {
        gpio_toggle(GPIOE, GPIO1);
    }
}
