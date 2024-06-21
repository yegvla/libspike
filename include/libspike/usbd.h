#ifndef LIBSPIKE_USBD_H
#define LIBSPIKE_USBD_H

#define USB1_DEV ((USB_OTG_DeviceTypeDef *)                             \
                  (USB_OTG_HS_PERIPH_BASE + USB_OTG_DEVICE_BASE))

#define USB_EP_OUT(i) ((USB_OTG_OUTEndpointTypeDef *)                        \
                       ((USB_OTG_HS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE) \
                        + ((i) * USB_OTG_EP_REG_SIZE)))

#define USB_EP_IN(i)  ((USB_OTG_INEndpointTypeDef *)                        \
                       ((USB_OTG_HS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE) \
                        + ((i) * USB_OTG_EP_REG_SIZE)))

#define USBD_GPIO_PORT GPIOA
#define USBD_GPIO_VBUS GPIO9
#define USBD_GPIO_DM   GPIO11
#define USBD_GPIO_DP   GPIO12
#define USBD_GPIO_DIFF (GPIO11 | GPIO12)

void usbd_init(void);

#endif /* LIBSPIKE_USBD_H */
