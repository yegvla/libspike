#ifndef LIBSPIKE_RCC_H
#define LIBSPIKE_RCC_H

#include <stm32h7xx.h>
#include <libspike/pwr.h>
#include <libspike/flash.h>
#include <stdbool.h>
#include <stdint.h>

/* Address offset (found in reference manual) + bit position.  Used for
 * `rcc_enable_clock` to specify the clock register and the bit using only one
 * value. */
#define OFFSET(REG, BIT) ((REG) << 8) | (BIT)

enum rcc_peripheral {
    /* AHB3 */
    RCC_MDMA = OFFSET(0x0D4, 0),
    RCC_DMA2D = OFFSET(0x0D4, 4),
    RCC_FMC = OFFSET(0x0D4, 12),
    RCC_OCTOSPI1 = OFFSET(0x0D4, 14),
    RCC_SDMMC1 = OFFSET(0x0D4, 16),
    RCC_OCTOSPI2 = OFFSET(0x0D4, 19),
    RCC_IOMNGR = OFFSET(0x0D4, 21),
    RCC_OTFD1 = OFFSET(0x0D4, 22),
    RCC_OTFD2 = OFFSET(0x0D4, 23),
    /* AHB1 */
    RCC_DMA1 = OFFSET(0x0D8, 0),
    RCC_DMA2 = OFFSET(0x0D8, 1),
    RCC_ADC12 = OFFSET(0x0D8, 5),
    RCC_ETH1MAC = OFFSET(0x0D8, 15),
    RCC_ETH1TX = OFFSET(0x0D8, 16),
    RCC_ETH1RX = OFFSET(0x0D8, 17),
    RCC_USB1OTGHS = OFFSET(0x0D8, 25),
    RCC_USB1OTGHSULPI = OFFSET(0x0D8, 26),
    /* AHB2 */
    RCC_DCMI_PSSI = OFFSET(0x0DC, 0),
    RCC_CRYPT = OFFSET(0x0DC, 4),
    RCC_HASH = OFFSET(0x0DC, 5),
    RCC_RNG = OFFSET(0x0DC, 6),
    RCC_SDMMC2 = OFFSET(0x0DC, 9),
    RCC_FMAC = OFFSET(0x0DC, 16),
    RCC_CORDIC = OFFSET(0x0DC, 17),
    RCC_SRAM1 = OFFSET(0x0DC, 29),
    RCC_SRAM2 = OFFSET(0x0DC, 30),
    /* AHB4 */
    RCC_GPIOA = OFFSET(0x0E0, 0),
    RCC_GPIOB = OFFSET(0x0E0, 1),
    RCC_GPIOC = OFFSET(0x0E0, 2),
    RCC_GPIOD = OFFSET(0x0E0, 3),
    RCC_GPIOE = OFFSET(0x0E0, 4),
    RCC_GPIOF = OFFSET(0x0E0, 5),
    RCC_GPIOG = OFFSET(0x0E0, 6),
    RCC_GPIOH = OFFSET(0x0E0, 7),
    RCC_GPIOJ = OFFSET(0x0E0, 9),
    RCC_GPIOK = OFFSET(0x0E0, 10),
    RCC_CRC = OFFSET(0x0E0, 19),
    RCC_BDMA = OFFSET(0x0E0, 21),
    RCC_ADC3 = OFFSET(0x0E0, 24),
    RCC_HSEM = OFFSET(0x0E0, 25),
    RCC_BKPRAM = OFFSET(0x0E0, 28),
    /* APB3 */
    RCC_LTDC = OFFSET(0x0E4, 3),
    RCC_WWDG1 = OFFSET(0x0E4, 6),
    /* APB1L */
    RCC_TIM2 = OFFSET(0x0E8, 0),
    RCC_TIM3 = OFFSET(0x0E8, 1),
    RCC_TIM4 = OFFSET(0x0E8, 2),
    RCC_TIM5 = OFFSET(0x0E8, 3),
    RCC_TIM6 = OFFSET(0x0E8, 4),
    RCC_TIM7 = OFFSET(0x0E8, 5),
    RCC_TIM12 = OFFSET(0x0E8, 6),
    RCC_TIM13 = OFFSET(0x0E8, 7),
    RCC_TIM14 = OFFSET(0x0E8, 8),
    RCC_LPTIM1 = OFFSET(0x0E8, 9),
    RCC_SPI2 = OFFSET(0x0E8, 14),
    RCC_SPI3 = OFFSET(0x0E8, 15),
    RCC_SPDIFRX = OFFSET(0x0E8, 16),
    RCC_UART2 = OFFSET(0x0E8, 17),
    RCC_UART3 = OFFSET(0x0E8, 18),
    RCC_UART4 = OFFSET(0x0E8, 19),
    RCC_UART5 = OFFSET(0x0E8, 20),
    RCC_I2C1 = OFFSET(0x0E8, 21),
    RCC_I2C2 = OFFSET(0x0E8, 22),
    RCC_I2C3 = OFFSET(0x0E8, 23),
    RCC_I2C5 = OFFSET(0x0E8, 25),
    RCC_CEC = OFFSET(0x0E8, 27),
    RCC_DAC12 = OFFSET(0x0E8, 29),
    RCC_UART7 = OFFSET(0x0E8, 30),
    RCC_UART8 = OFFSET(0x0E8, 31),
    /* APB1H */
    RCC_CRS = OFFSET(0x0EC, 1),
    RCC_SWPMI = OFFSET(0x0EC, 2),
    RCC_OPAMP = OFFSET(0x0EC, 4),
    RCC_MDIOS = OFFSET(0x0EC, 5),
    RCC_FDCAN = OFFSET(0x0EC, 8),
    RCC_TIM23 = OFFSET(0x0EC, 24),
    RCC_TIM24 = OFFSET(0x0EC, 25),
    /* APB2 Peripherals */
    RCC_TIM1 = OFFSET(0x0F0, 0),
    RCC_TIM8 = OFFSET(0x0F0, 1),
    RCC_USART1 = OFFSET(0x0F0, 4),
    RCC_USART6 = OFFSET(0x0F0, 5),
    RCC_USART9 = OFFSET(0x0F0, 6),
    RCC_USART10 = OFFSET(0x0F0, 7),
    RCC_SPI1 = OFFSET(0x0F0, 12),
    RCC_SPI4 = OFFSET(0x0F0, 13),
    RCC_TIM15 = OFFSET(0x0F0, 16),
    RCC_TIM16 = OFFSET(0x0F0, 17),
    RCC_TIM17 = OFFSET(0x0F0, 18),
    RCC_SPI5 = OFFSET(0x0F0, 20),
    RCC_SAI1 = OFFSET(0x0F0, 22),
    RCC_DFSDM1 = OFFSET(0x0F0, 30),
    /* APB4 */
    RCC_SYSCFG = OFFSET(0x0F4, 1),
    RCC_LPUART1 = OFFSET(0x0F4, 3),
    RCC_SPI6 = OFFSET(0x0F4, 5),
    RCC_I2C4 = OFFSET(0x0F4, 7),
    RCC_LPTIM2 = OFFSET(0x0F4, 9),
    RCC_LPTIM3 = OFFSET(0x0F4, 10),
    RCC_LPTIM4 = OFFSET(0x0F4, 11),
    RCC_LPTIM5 = OFFSET(0x0F4, 12),
    RCC_COMP12 = OFFSET(0x0F4, 14),
    RCC_VREF = OFFSET(0x0F4, 15),
    RCC_RTCAPB = OFFSET(0x0F4, 16),
    RCC_SAI4 = OFFSET(0x0F4, 21),
    RCC_DTS = OFFSET(0x0F4, 26)
};

#undef OFFSET

enum rcc_vci {
    RCC_VCI_RANGE_1_2_MHZ  = 0,  /* Range 0 */
    RCC_VCI_RANGE_2_4_MHZ  = 1,  /* Range 1 */
    RCC_VCI_RANGE_4_8_MHZ  = 2,  /* Range 2 */
    RCC_VCI_RANGE_8_16_MHZ = 3,  /* Range 3 */
};

enum rcc_vco {
    RCC_VCO_WIDE   = 0,
    RCC_VCO_MEDIUM = 1
};

/* Values are only used internally. */
enum rcc_oscillator {
    RCC_OSCILLATOR_NONE  = 0x00,
    RCC_OSCILLATOR_HSE   = 0x01,
    RCC_OSCILLATOR_HSI   = 0x02,
    RCC_OSCILLATOR_LSE   = 0x04,
    RCC_OSCILLATOR_LSI   = 0x08,
    RCC_OSCILLATOR_CSI   = 0x10,
    RCC_OSCILLATOR_HSI48 = 0x20,
};

#define RCC_OSCILLATOR_CHECK_HSE(X)   (X & RCC_OSCILLATOR_HSE)
#define RCC_OSCILLATOR_CHECK_HSI(X)   (X & RCC_OSCILLATOR_HSI)
#define RCC_OSCILLATOR_CHECK_LSE(X)   (X & RCC_OSCILLATOR_LSE)
#define RCC_OSCILLATOR_CHECK_LSI(X)   (X & RCC_OSCILLATOR_LSI)
#define RCC_OSCILLATOR_CHECK_CSI(X)   (X & RCC_OSCILLATOR_CSI)
#define RCC_OSCILLATOR_CHECK_HSI48(X) (X & RCC_OSCILLATOR_HSI48)

enum rcc_pll_source {
    RCC_PLL_SOURCE_HSI = RCC_PLLCKSELR_PLLSRC_HSI,
    RCC_PLL_SOURCE_CSI = RCC_PLLCKSELR_PLLSRC_CSI,
    RCC_PLL_SOURCE_HSE = RCC_PLLCKSELR_PLLSRC_HSE
};

enum rcc_sysclk_source {
    RCC_SYSCLK_SOURCE_CSI = RCC_CFGR_SW_CSI,
    RCC_SYSCLK_SOURCE_HSI = RCC_CFGR_SW_HSI,
    RCC_SYSCLK_SOURCE_HSE = RCC_CFGR_SW_HSE,
    RCC_SYSCLK_SOURCE_PLL = RCC_CFGR_SW_PLL1
};

enum rcc_cpre_div {
    RCC_CPRE_DIV1   = RCC_D1CFGR_D1CPRE_DIV1,
    RCC_CPRE_DIV2   = RCC_D1CFGR_D1CPRE_DIV2,
    RCC_CPRE_DIV4   = RCC_D1CFGR_D1CPRE_DIV4,
    RCC_CPRE_DIV8   = RCC_D1CFGR_D1CPRE_DIV8,
    RCC_CPRE_DIV16  = RCC_D1CFGR_D1CPRE_DIV16,
    RCC_CPRE_DIV64  = RCC_D1CFGR_D1CPRE_DIV64,
    RCC_CPRE_DIV128 = RCC_D1CFGR_D1CPRE_DIV128,
    RCC_CPRE_DIV256 = RCC_D1CFGR_D1CPRE_DIV256,
    RCC_CPRE_DIV512 = RCC_D1CFGR_D1CPRE_DIV512
};

enum rcc_hpre_div {
    RCC_HPRE_DIV1   = RCC_D1CFGR_HPRE_DIV1,
    RCC_HPRE_DIV2   = RCC_D1CFGR_HPRE_DIV2,
    RCC_HPRE_DIV4   = RCC_D1CFGR_HPRE_DIV4,
    RCC_HPRE_DIV8   = RCC_D1CFGR_HPRE_DIV8,
    RCC_HPRE_DIV16  = RCC_D1CFGR_HPRE_DIV16,
    RCC_HPRE_DIV64  = RCC_D1CFGR_HPRE_DIV64,
    RCC_HPRE_DIV128 = RCC_D1CFGR_HPRE_DIV128,
    RCC_HPRE_DIV256 = RCC_D1CFGR_HPRE_DIV256,
    RCC_HPRE_DIV512 = RCC_D1CFGR_HPRE_DIV512
};

enum rcc_ppre3_div {
    RCC_PPRE3_DIV1  = RCC_D1CFGR_D1PPRE_DIV1,
    RCC_PPRE3_DIV2  = RCC_D1CFGR_D1PPRE_DIV2,
    RCC_PPRE3_DIV4  = RCC_D1CFGR_D1PPRE_DIV4,
    RCC_PPRE3_DIV8  = RCC_D1CFGR_D1PPRE_DIV8,
    RCC_PPRE3_DIV16 = RCC_D1CFGR_D1PPRE_DIV16
};


enum rcc_ppre1_div {
    RCC_PPRE1_DIV1  = RCC_D2CFGR_D2PPRE1_DIV1,
    RCC_PPRE1_DIV2  = RCC_D2CFGR_D2PPRE1_DIV2,
    RCC_PPRE1_DIV4  = RCC_D2CFGR_D2PPRE1_DIV4,
    RCC_PPRE1_DIV8  = RCC_D2CFGR_D2PPRE1_DIV8,
    RCC_PPRE1_DIV16 = RCC_D2CFGR_D2PPRE1_DIV16
};

enum rcc_ppre2_div {
    RCC_PPRE2_DIV1  = RCC_D2CFGR_D2PPRE2_DIV1,
    RCC_PPRE2_DIV2  = RCC_D2CFGR_D2PPRE2_DIV2,
    RCC_PPRE2_DIV4  = RCC_D2CFGR_D2PPRE2_DIV4,
    RCC_PPRE2_DIV8  = RCC_D2CFGR_D2PPRE2_DIV8,
    RCC_PPRE2_DIV16 = RCC_D2CFGR_D2PPRE2_DIV16
};

enum rcc_ppre4_div {
    RCC_PPRE4_DIV1  = RCC_D3CFGR_D3PPRE_DIV1,
    RCC_PPRE4_DIV2  = RCC_D3CFGR_D3PPRE_DIV2,
    RCC_PPRE4_DIV4  = RCC_D3CFGR_D3PPRE_DIV4,
    RCC_PPRE4_DIV8  = RCC_D3CFGR_D3PPRE_DIV8,
    RCC_PPRE4_DIV16 = RCC_D3CFGR_D3PPRE_DIV16
};

/* TODO: I would like to have a way to calculate a matching rcc_config using the
 * desired frequencies.  Something like STM32Cube does but using a macro/method,
 * but probably won't happen anytime soon... */
/* TODO2: add mco stuff... */
/* TODO3: lse bypass */
struct rcc_clock_config {
    enum rcc_oscillator active_osci;
    bool bypass_hse;
    enum rcc_sysclk_source sysclk_src;
    enum rcc_pll_source pll_src;
    struct rcc_pll_config {
        uint8_t divm;
        uint16_t divn;
        uint8_t divp;
        uint8_t divq;
        uint8_t divr;
        uint16_t fracn;
        enum rcc_vci rge;
        enum rcc_vco vcosel;
    } pll1, pll2, pll3;
    enum flash_latency flash_latency;
    enum rcc_cpre_div cpre;
    enum rcc_hpre_div hpre;
    enum rcc_ppre3_div ppre3;
    enum rcc_ppre1_div ppre1;
    enum rcc_ppre2_div ppre2;
    enum rcc_ppre4_div ppre4;
};

enum rcc_lse_drive {
    RCC_LSE_DRIVE_LOW           = 0,
    RCC_LSE_DRIVE_MEDIUM_LOW    = RCC_BDCR_LSEDRV_0,
    RCC_LSE_DRIVE_MEDIUM_HIGH   = RCC_BDCR_LSEDRV_1,
    RCC_LSE_DRIVE_HIGH          = RCC_BDCR_LSEDRV
};

void rcc_lse_drive(enum rcc_lse_drive drive);

int rcc_configure_clocks(struct rcc_clock_config config);

void rcc_enable_clock(enum rcc_peripheral clk);
void rcc_disable_clock(enum rcc_peripheral clk);

/* Peripheral clock selection. */

enum rcc_usb_clksel {
    RCC_USB_CLKSEL_DISABLE = 0b00 << RCC_D2CCIP2R_USBSEL_Pos,
    RCC_USB_CLKSEL_PLL1Q   = 0b01 << RCC_D2CCIP2R_USBSEL_Pos,
    RCC_USB_CLKSEL_PLL3Q   = 0b10 << RCC_D2CCIP2R_USBSEL_Pos,
    RCC_USB_CLKSEL_HSI48   = 0b11 << RCC_D2CCIP2R_USBSEL_Pos
};

void rcc_usb_clock(enum rcc_usb_clksel sel);

#endif /* LIBSPIKE_RCC_H */
