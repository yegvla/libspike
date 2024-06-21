#ifndef LIBSPIKE_IRQ_H
#define LIBSPIKE_IRQ_H
void wwdg_isr(void);
void pvd_avd_isr(void);
void tamp_stamp_isr(void);
void rtc_wkup_isr(void);
void flash_isr(void);
void rcc_isr(void);
void exti0_isr(void);
void exti1_isr(void);
void exti2_isr(void);
void exti3_isr(void);
void exti4_isr(void);
void dma1_stream0_isr(void);
void dma1_stream1_isr(void);
void dma1_stream2_isr(void);
void dma1_stream3_isr(void);
void dma1_stream4_isr(void);
void dma1_stream5_isr(void);
void dma1_stream6_isr(void);
void adc_isr(void);
void fdcan1_it0_isr(void);
void fdcan2_it0_isr(void);
void fdcan1_it1_isr(void);
void fdcan2_it1_isr(void);
void exti9_5_isr(void);
void tim1_brk_isr(void);
void tim1_up_isr(void);
void tim1_trg_com_isr(void);
void tim1_cc_isr(void);
void tim2_isr(void);
void tim3_isr(void);
void tim4_isr(void);
void i2c1_ev_isr(void);
void i2c1_er_isr(void);
void i2c2_ev_isr(void);
void i2c2_er_isr(void);
void spi1_isr(void);
void spi2_isr(void);
void usart1_isr(void);
void usart2_isr(void);
void usart3_isr(void);
void exti15_10_isr(void);
void rtc_alarm_isr(void);
void tim8_brk_tim12_isr(void);
void tim8_up_tim13_isr(void);
void tim8_trg_com_tim14_isr(void);
void tim8_cc_isr(void);
void dma1_stream7_isr(void);
void fmc_isr(void);
void sdmmc1_isr(void);
void tim5_isr(void);
void spi3_isr(void);
void uart4_isr(void);
void uart5_isr(void);
void tim6_dac_isr(void);
void tim7_isr(void);
void dma2_stream0_isr(void);
void dma2_stream1_isr(void);
void dma2_stream2_isr(void);
void dma2_stream3_isr(void);
void dma2_stream4_isr(void);
void eth_isr(void);
void eth_wkup_isr(void);
void fdcan_cal_isr(void);
void dma2_stream5_isr(void);
void dma2_stream6_isr(void);
void dma2_stream7_isr(void);
void usart6_isr(void);
void i2c3_ev_isr(void);
void i2c3_er_isr(void);
void otg_hs_ep1_out_isr(void);
void otg_hs_ep1_in_isr(void);
void otg_hs_wkup_isr(void);
void otg_hs_isr(void);
void dcmi_pssi_isr(void);
void rng_isr(void);
void fpu_isr(void);
void uart7_isr(void);
void uart8_isr(void);
void spi4_isr(void);
void spi5_isr(void);
void spi6_isr(void);
void sai1_isr(void);
void ltdc_isr(void);
void ltdc_er_isr(void);
void dma2d_isr(void);
void octospi1_isr(void);
void lptim1_isr(void);
void cec_isr(void);
void i2c4_ev_isr(void);
void i2c4_er_isr(void);
void spdif_rx_isr(void);
void dmamux1_ovr_isr(void);
void dfsdm1_flt0_isr(void);
void dfsdm1_flt1_isr(void);
void dfsdm1_flt2_isr(void);
void dfsdm1_flt3_isr(void);
void swpmi1_isr(void);
void tim15_isr(void);
void tim16_isr(void);
void tim17_isr(void);
void mdios_wkup_isr(void);
void mdios_isr(void);
void mdma_isr(void);
void sdmmc2_isr(void);
void hsem1_isr(void);
void adc3_isr(void);
void dmamux2_ovr_isr(void);
void bdma_channel0_isr(void);
void bdma_channel1_isr(void);
void bdma_channel2_isr(void);
void bdma_channel3_isr(void);
void bdma_channel4_isr(void);
void bdma_channel5_isr(void);
void bdma_channel6_isr(void);
void bdma_channel7_isr(void);
void comp_isr(void);
void lptim2_isr(void);
void lptim3_isr(void);
void lptim4_isr(void);
void lptim5_isr(void);
void lpuart1_isr(void);
void crs_isr(void);
void ecc_isr(void);
void sai4_isr(void);
void dts_isr(void);
void wakeup_pin_isr(void);
void octospi2_isr(void);
void fmac_isr(void);
void cordic_isr(void);
void uart9_isr(void);
void usart10_isr(void);
void i2c5_ev_isr(void);
void i2c5_er_isr(void);
void fdcan3_it0_isr(void);
void fdcan3_it1_isr(void);
void tim23_isr(void);
void tim24_isr(void);

#define VECTOR_IRQ_COUNT 163
#define VECTOR_IRQ_LIST { \
    [0] = wwdg_isr, \
    [1] = pvd_avd_isr, \
    [2] = tamp_stamp_isr, \
    [3] = rtc_wkup_isr, \
    [4] = flash_isr, \
    [5] = rcc_isr, \
    [6] = exti0_isr, \
    [7] = exti1_isr, \
    [8] = exti2_isr, \
    [9] = exti3_isr, \
    [10] = exti4_isr, \
    [11] = dma1_stream0_isr, \
    [12] = dma1_stream1_isr, \
    [13] = dma1_stream2_isr, \
    [14] = dma1_stream3_isr, \
    [15] = dma1_stream4_isr, \
    [16] = dma1_stream5_isr, \
    [17] = dma1_stream6_isr, \
    [18] = adc_isr, \
    [19] = fdcan1_it0_isr, \
    [20] = fdcan2_it0_isr, \
    [21] = fdcan1_it1_isr, \
    [22] = fdcan2_it1_isr, \
    [23] = exti9_5_isr, \
    [24] = tim1_brk_isr, \
    [25] = tim1_up_isr, \
    [26] = tim1_trg_com_isr, \
    [27] = tim1_cc_isr, \
    [28] = tim2_isr, \
    [29] = tim3_isr, \
    [30] = tim4_isr, \
    [31] = i2c1_ev_isr, \
    [32] = i2c1_er_isr, \
    [33] = i2c2_ev_isr, \
    [34] = i2c2_er_isr, \
    [35] = spi1_isr, \
    [36] = spi2_isr, \
    [37] = usart1_isr, \
    [38] = usart2_isr, \
    [39] = usart3_isr, \
    [40] = exti15_10_isr, \
    [41] = rtc_alarm_isr, \
    [43] = tim8_brk_tim12_isr, \
    [44] = tim8_up_tim13_isr, \
    [45] = tim8_trg_com_tim14_isr, \
    [46] = tim8_cc_isr, \
    [47] = dma1_stream7_isr, \
    [48] = fmc_isr, \
    [49] = sdmmc1_isr, \
    [50] = tim5_isr, \
    [51] = spi3_isr, \
    [52] = uart4_isr, \
    [53] = uart5_isr, \
    [54] = tim6_dac_isr, \
    [55] = tim7_isr, \
    [56] = dma2_stream0_isr, \
    [57] = dma2_stream1_isr, \
    [58] = dma2_stream2_isr, \
    [59] = dma2_stream3_isr, \
    [60] = dma2_stream4_isr, \
    [61] = eth_isr, \
    [62] = eth_wkup_isr, \
    [63] = fdcan_cal_isr, \
    [68] = dma2_stream5_isr, \
    [69] = dma2_stream6_isr, \
    [70] = dma2_stream7_isr, \
    [71] = usart6_isr, \
    [72] = i2c3_ev_isr, \
    [73] = i2c3_er_isr, \
    [74] = otg_hs_ep1_out_isr, \
    [75] = otg_hs_ep1_in_isr, \
    [76] = otg_hs_wkup_isr, \
    [77] = otg_hs_isr, \
    [78] = dcmi_pssi_isr, \
    [80] = rng_isr, \
    [81] = fpu_isr, \
    [82] = uart7_isr, \
    [83] = uart8_isr, \
    [84] = spi4_isr, \
    [85] = spi5_isr, \
    [86] = spi6_isr, \
    [87] = sai1_isr, \
    [88] = ltdc_isr, \
    [89] = ltdc_er_isr, \
    [90] = dma2d_isr, \
    [92] = octospi1_isr, \
    [93] = lptim1_isr, \
    [94] = cec_isr, \
    [95] = i2c4_ev_isr, \
    [96] = i2c4_er_isr, \
    [97] = spdif_rx_isr, \
    [102] = dmamux1_ovr_isr, \
    [110] = dfsdm1_flt0_isr, \
    [111] = dfsdm1_flt1_isr, \
    [112] = dfsdm1_flt2_isr, \
    [113] = dfsdm1_flt3_isr, \
    [115] = swpmi1_isr, \
    [116] = tim15_isr, \
    [117] = tim16_isr, \
    [118] = tim17_isr, \
    [119] = mdios_wkup_isr, \
    [120] = mdios_isr, \
    [122] = mdma_isr, \
    [124] = sdmmc2_isr, \
    [125] = hsem1_isr, \
    [127] = adc3_isr, \
    [128] = dmamux2_ovr_isr, \
    [129] = bdma_channel0_isr, \
    [130] = bdma_channel1_isr, \
    [131] = bdma_channel2_isr, \
    [132] = bdma_channel3_isr, \
    [133] = bdma_channel4_isr, \
    [134] = bdma_channel5_isr, \
    [135] = bdma_channel6_isr, \
    [136] = bdma_channel7_isr, \
    [137] = comp_isr, \
    [138] = lptim2_isr, \
    [139] = lptim3_isr, \
    [140] = lptim4_isr, \
    [141] = lptim5_isr, \
    [142] = lpuart1_isr, \
    [144] = crs_isr, \
    [145] = ecc_isr, \
    [146] = sai4_isr, \
    [147] = dts_isr, \
    [149] = wakeup_pin_isr, \
    [150] = octospi2_isr, \
    [153] = fmac_isr, \
    [154] = cordic_isr, \
    [155] = uart9_isr, \
    [156] = usart10_isr, \
    [157] = i2c5_ev_isr, \
    [158] = i2c5_er_isr, \
    [159] = fdcan3_it0_isr, \
    [160] = fdcan3_it1_isr, \
    [161] = tim23_isr, \
    [162] = tim24_isr, \
}
#endif  /* define LIBSPIKE_IRQ_H */
