#include "stm32h723xx.h"
#include <libspike/flash.h>
#include <libspike/rcc.h>
#include <libspike/pwr.h>
#include <libspike/utils.h>
#include <stm32h7xx.h>

inline void rcc_enable_clock(enum rcc_peripheral clk)
{
    reg32_t dummy;
    uint8_t bit_offset = clk & 0xff;
    uint8_t register_offset = clk >> 8;
    reg32_t *clock_register = (reg32_t *) (RCC_BASE + register_offset);
    *clock_register |= 1 << bit_offset;
    dummy = READ_BIT(*clock_register, 1 << bit_offset);
    (void) dummy;
}

inline void rcc_disable_clock(enum rcc_peripheral clk)
{
    uint8_t bit_offset = clk & 0xff;
    uint8_t register_offset = clk >> 8;
    reg32_t *clock_register = (reg32_t *) (RCC_BASE + register_offset);
    *clock_register &= ~(1 << bit_offset);
}

inline void rcc_lse_drive(enum rcc_lse_drive drive)
{
    MODIFY_REG(RCC->BDCR, RCC_BDCR_LSEDRV, drive);
}

int rcc_configure_clocks(struct rcc_clock_config config)
{
    while (!(PWR->CSR1 & PWR_CSR1_ACTVOSRDY));
    /* Switch to interal oscillator if we are not already using it.*/
    if ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) {
        RCC->CR |= RCC_CR_HSION;
        RCC->CFGR &= ~RCC_CFGR_SW;
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); /* Timeout. */
        RCC->CR = RCC_CR_HSION;
    }

    /* Enable oscillators. */
    /* TODO: Add all oscillators */
    if (RCC_OSCILLATOR_CHECK_HSE(config.active_osci)) {
        if (config.bypass_hse) {
            RCC->CR |= RCC_CR_HSEBYP;
        }
        RCC->CR |= RCC_CR_HSEON;
        while (!(RCC->CR & RCC_CR_HSERDY)); /* Timeout. */
    }

    if (RCC_OSCILLATOR_CHECK_LSE(config.active_osci)) {
        /* Configure drive capability. */
        pwr_enable_bkup_accesss();
        rcc_lse_drive(RCC_LSE_DRIVE_LOW);
        /* Enable write access to backup domain. */
        PWR->CR1 |= PWR_CR1_DBP;
        while (!(PWR->CR1 & PWR_CR1_DBP)); /* Timeout. */
        RCC->BDCR |= RCC_BDCR_LSEON;
        while (!(RCC->BDCR & RCC_BDCR_LSERDY)); /* Timeout. */
    }

    /* Configure PLL. */
    RCC->CR &= ~RCC_CR_PLL1ON;
    while (RCC->CR & RCC_CR_PLL1RDY);

    /* Set the clock source of PLL1 and the DIVM registers of PLL1-3. */
    const uint32_t divm1 = config.pll1.divm << RCC_PLLCKSELR_DIVM1_Pos;
    const uint32_t divm2 = config.pll2.divm << RCC_PLLCKSELR_DIVM2_Pos;
    const uint32_t divm3 = config.pll3.divm << RCC_PLLCKSELR_DIVM3_Pos;
    const uint32_t mask = RCC_PLLCKSELR_PLLSRC | RCC_PLLCKSELR_DIVM1
        | RCC_PLLCKSELR_DIVM2 | RCC_PLLCKSELR_DIVM3;
    const uint32_t set = divm1 | divm2 | divm3 | config.pll_src;
    MODIFY_REG(RCC->PLLCKSELR, mask, set);

    /* Configure PLL1 */
    RCC->PLL1DIVR &= ~(RCC_PLL1DIVR_N1 | RCC_PLL1DIVR_P1 | RCC_PLL1DIVR_Q1
                       | RCC_PLL1DIVR_R1);
    
    RCC->PLL1DIVR |= (config.pll1.divn - 1) << RCC_PLL1DIVR_N1_Pos
        | (config.pll1.divp - 1) << RCC_PLL1DIVR_P1_Pos
        | (config.pll1.divq - 1) << RCC_PLL1DIVR_Q1_Pos
        | (config.pll1.divr - 1) << RCC_PLL1DIVR_R1_Pos;

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLL1FRACEN;
    
    MODIFY_REG(RCC->PLL1FRACR, RCC_PLL1FRACR_FRACN1,
               config.pll1.fracn << RCC_PLL1FRACR_FRACN1_Pos);
    
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL1RGE,
               config.pll1.rge << RCC_PLLCFGR_PLL1RGE_Pos);
    
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL1VCOSEL,
               config.pll1.vcosel << RCC_PLLCFGR_PLL1VCOSEL_Pos);
    
    RCC->PLLCFGR |= RCC_PLLCFGR_DIVP1EN
        | RCC_PLLCFGR_DIVQ1EN
        | RCC_PLLCFGR_DIVR1EN;
    
    if (config.pll1.fracn)
        RCC->PLLCFGR |= RCC_PLLCFGR_PLL1FRACEN;
    
    RCC->CR |= RCC_CR_PLL1ON;
    while (!(RCC->CR & RCC_CR_PLL1RDY));

    /* Configure PLL2 */
    RCC->CR &= ~RCC_CR_PLL2ON;
    while (RCC->CR & RCC_CR_PLL2RDY);
    
    RCC->PLL2DIVR &= ~(RCC_PLL2DIVR_N2 | RCC_PLL2DIVR_P2 | RCC_PLL2DIVR_Q2
                       | RCC_PLL2DIVR_R2);
    
    RCC->PLL2DIVR |= (config.pll2.divn - 1) << RCC_PLL2DIVR_N2_Pos
        | (config.pll2.divp - 1) << RCC_PLL2DIVR_P2_Pos
        | (config.pll2.divq - 1) << RCC_PLL2DIVR_Q2_Pos
        | (config.pll2.divr - 1) << RCC_PLL2DIVR_R2_Pos;
    
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLL2FRACEN;
    
    MODIFY_REG(RCC->PLL2FRACR, RCC_PLL2FRACR_FRACN2,
               config.pll2.fracn << RCC_PLL2FRACR_FRACN2_Pos);
    
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL2RGE,
               config.pll2.rge << RCC_PLLCFGR_PLL2RGE_Pos);
    
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL2VCOSEL,
               config.pll2.vcosel << RCC_PLLCFGR_PLL2VCOSEL_Pos);
    
    RCC->PLLCFGR |= RCC_PLLCFGR_DIVP2EN
        | RCC_PLLCFGR_DIVQ2EN
        | RCC_PLLCFGR_DIVR2EN
        | RCC_PLLCFGR_PLL2FRACEN;

    RCC->PLLCFGR |= RCC_PLLCFGR_PLL2FRACEN;
    
    RCC->CR |= RCC_CR_PLL2ON;
    while (!(RCC->CR & RCC_CR_PLL2RDY));

    /* Configure PLL3 */
    RCC->CR &= ~RCC_CR_PLL3ON;
    while (RCC->CR & RCC_CR_PLL3RDY);
    
    RCC->PLL3DIVR &= ~(RCC_PLL3DIVR_N3 | RCC_PLL3DIVR_P3 | RCC_PLL3DIVR_Q3
                       | RCC_PLL3DIVR_R3);
    
    RCC->PLL3DIVR |= (config.pll3.divn - 1) << RCC_PLL3DIVR_N3_Pos
        | (config.pll3.divp - 1) << RCC_PLL3DIVR_P3_Pos
        | (config.pll3.divq - 1) << RCC_PLL3DIVR_Q3_Pos
        | (config.pll3.divr - 1) << RCC_PLL3DIVR_R3_Pos;
    
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLL3FRACEN;
    
    MODIFY_REG(RCC->PLL3FRACR, RCC_PLL3FRACR_FRACN3,
               config.pll3.fracn << RCC_PLL3FRACR_FRACN3_Pos);
    
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL3RGE,
               config.pll3.rge << RCC_PLLCFGR_PLL3RGE_Pos);
    
    MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLL3VCOSEL,
               config.pll3.vcosel << RCC_PLLCFGR_PLL3VCOSEL_Pos);
    
    RCC->PLLCFGR |= RCC_PLLCFGR_DIVP3EN
        | RCC_PLLCFGR_DIVQ3EN
        | RCC_PLLCFGR_DIVR3EN
        | RCC_PLLCFGR_PLL3FRACEN;

    RCC->PLLCFGR |= RCC_PLLCFGR_PLL3FRACEN;
    
    RCC->CR |= RCC_CR_PLL3ON;
    while (!(RCC->CR & RCC_CR_PLL3RDY));

    flash_set_latency(config.flash_latency);

    MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_D1PPRE, config.ppre3);
    MODIFY_REG(RCC->D2CFGR, RCC_D2CFGR_D2PPRE1, config.ppre1);
    MODIFY_REG(RCC->D2CFGR, RCC_D2CFGR_D2PPRE2, config.ppre2);
    MODIFY_REG(RCC->D3CFGR, RCC_D3CFGR_D3PPRE, config.ppre4);
    MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_HPRE, config.hpre);
    MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_D1CPRE, config.cpre);

    /* Finally, switch the system clock. */
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, config.sysclk_src);
    while ((RCC->CFGR & RCC_CFGR_SWS) != (config.sysclk_src << RCC_CFGR_SWS_Pos));
    return 0;
}

void rcc_usb_clock(enum rcc_usb_clksel sel)
{
    MODIFY_REG(RCC->D2CCIP2R, RCC_D2CCIP2R_USBSEL, sel);
}
