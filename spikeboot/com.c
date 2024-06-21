#include <libspike/rcc.h>
#include <stm32h7xx.h>
#include <libspike/usbd.h>
#include <libspike/irq.h>
#include <spikeboot/com.h>
#include <stdio.h>

void otg_hs_isr(void)
{
    printf("USBINT: %08x\n", USB1_OTG_HS->GINTSTS);
}

void com_init(void)
{
    rcc_usb_clock(RCC_USB_CLKSEL_PLL3Q);
    usbd_init();
}
