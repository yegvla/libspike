#ifndef LIBSPIKE_GPIO_H
#define LIBSPIKE_GPIO_H

#include <stm32h7xx.h>
#include <stdint.h>
#include <stdbool.h>

/* Some aliases */
#define GPIO0 GPIO_ODR_OD0_Msk
#define GPIO1 GPIO_ODR_OD1_Msk
#define GPIO2 GPIO_ODR_OD2_Msk
#define GPIO3 GPIO_ODR_OD3_Msk
#define GPIO4 GPIO_ODR_OD4_Msk
#define GPIO5 GPIO_ODR_OD5_Msk
#define GPIO6 GPIO_ODR_OD6_Msk
#define GPIO7 GPIO_ODR_OD7_Msk
#define GPIO8 GPIO_ODR_OD8_Msk
#define GPIO9 GPIO_ODR_OD9_Msk
#define GPIO10 GPIO_ODR_OD10_Msk
#define GPIO11 GPIO_ODR_OD11_Msk
#define GPIO12 GPIO_ODR_OD12_Msk
#define GPIO13 GPIO_ODR_OD13_Msk
#define GPIO14 GPIO_ODR_OD14_Msk
#define GPIO15 GPIO_ODR_OD15_Msk
#define GPIO_ALL 0xffffU
#define GPIO_NONE 0x0000U

enum gpio_pupd_config {
    GPIO_PUPD_DISABLED = 0b00,
    GPIO_PUPD_PULL_UP = 0b01,
    GPIO_PUPD_PULL_DOWN = 0b10
};

enum gpio_speed_config {
    GPIO_SPEED_LOW = 0b00,
    GPIO_SPEED_MEDIUM = 0b01,
    GPIO_SPEED_HIGH = 0b10,
    GPIO_SPEED_VERY_HIGH = 0b11
};

enum gpio_mode_config {
    GPIO_MODE_INPUT = 0b00,
    GPIO_MODE_OUTPUT = 0b01,
    GPIO_MODE_AF = 0b10,
    GPIO_MODE_ANALOG = 0b11
};

void gpio_mode(GPIO_TypeDef *port, uint16_t pins, enum gpio_mode_config cfg);
void gpio_speed(GPIO_TypeDef *port, uint16_t pins, enum gpio_speed_config cfg);
void gpio_pupd(GPIO_TypeDef *port, uint16_t pins, enum gpio_pupd_config cfg);

void gpio_push_pull(GPIO_TypeDef *port, uint16_t mask);
void gpio_open_drain(GPIO_TypeDef *port, uint16_t mask);

void gpio_set(GPIO_TypeDef *port, uint16_t mask);
void gpio_clear(GPIO_TypeDef *port, uint16_t mask);
void gpio_write(GPIO_TypeDef *port, uint16_t pin, bool state);
void gpio_port_write(GPIO_TypeDef *port, uint16_t mask);
void gpio_toggle(GPIO_TypeDef *port, uint16_t mask);

uint16_t gpio_port_read(GPIO_TypeDef *port);
uint16_t gpio_read(GPIO_TypeDef *port, uint16_t mask);


#endif /* LIBSPIKE_GPIO_H */
