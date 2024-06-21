#include <libspike/gpio.h>
#include <libspike/rcc.h>
#include <stdint.h>
#include <stm32h723xx.h>
#include <stm32h7xx.h>
#include <libspike/nvic.h>
#include <libspike/usbd.h>

void usbd_init(void)
{
    /* Setup GPIOs. */
    rcc_enable_clock(RCC_GPIOA);
    gpio_mode(GPIOA, USBD_GPIO_DIFF, GPIO_MODE_AF);
    gpio_speed(GPIOA, USBD_GPIO_DIFF, GPIO_SPEED_VERY_HIGH);
    gpio_pupd(GPIOA, USBD_GPIO_DIFF, GPIO_PUPD_DISABLED);
    gpio_mode(GPIOA, USBD_GPIO_VBUS, GPIO_MODE_INPUT);
    gpio_pupd(GPIOA, USBD_GPIO_VBUS, GPIO_PUPD_DISABLED);
        
    /* Clock USB peripheral. */ 
    rcc_enable_clock(RCC_USB1OTGHS);

    /* Core initialization. */
    USB1_OTG_HS->GAHBCFG |= USB_OTG_GAHBCFG_GINT;

    USB1_OTG_HS->GINTMSK = USB_OTG_GINTMSK_USBRST
        /* | USB_OTG_GINTMSK_ENUMDNEM */
        /* | USB_OTG_GINTMSK_ESUSPM */
        /* | USB_OTG_GINTMSK_USBSUSPM */
        | USB_OTG_GINTMSK_SOFM
        | USB_OTG_GINTMSK_OEPINT
        | USB_OTG_GINTMSK_IEPINT
        | USB_OTG_GINTSTS_RXFLVL;

    USB1_OTG_HS->GCCFG = USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_VBDEN;

    USB1_OTG_HS->GUSBCFG = USB_OTG_GUSBCFG_FDMOD | USB_OTG_GUSBCFG_PHYSEL;
    MODIFY_REG(USB1_OTG_HS->GUSBCFG, USB_OTG_GUSBCFG_TRDT,
               0x6 << USB_OTG_GUSBCFG_TRDT_Pos);

    /* TODO */
    
    const uint32_t rx_fifo_size = 0x200;
    const uint32_t tx_ep0_fifo_size = 0x80;
    const uint32_t tx_ep1_fifo_size = 0x174; /* 320-(RX_FIFO_SIZE+TX_EP0_FIFO_SIZE) */
    
    USB1_OTG_HS->GRXFSIZ = rx_fifo_size;
    USB1_OTG_HS->DIEPTXF0_HNPTXFSIZ =
        ((tx_ep0_fifo_size) << USB_OTG_DIEPTXF_INEPTXFD_Pos) | rx_fifo_size;
    USB1_OTG_HS->DIEPTXF[0] =
        ((tx_ep1_fifo_size) << USB_OTG_DIEPTXF_INEPTXFD_Pos)
        | (rx_fifo_size + tx_ep0_fifo_size);

    for(uint_fast8_t i = 1; i < 9; ++i) {
        USB1_OTG_HS->DIEPTXF[i] = 0;
    }


    USB_EP_OUT(0)->DOEPTSIZ = 0;
    USB_EP_OUT(0)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT &
                                (1 << USB_OTG_DOEPTSIZ_PKTCNT_Pos));
    USB_EP_OUT(0)->DOEPTSIZ |= 64;
    USB_EP_OUT(0)->DOEPTSIZ |= USB_OTG_DOEPTSIZ_STUPCNT;
    USB_EP_OUT(0)->DOEPCTL |= USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA;

    USB1_DEV->DCFG |= USB_OTG_DCFG_DSPD;
    USB1_OTG_HS->GINTSTS = 0xffffffff;
    USB1_DEV->DCTL &= ~USB_OTG_DCTL_SDIS;

    /* Enable & set priority for interrupt. */
    nvic_set_priority(OTG_HS_IRQn, 8);
    nvic_enable_irq(OTG_HS_IRQn);
}
