#include <libspike/gpio.h>
#include <stdint.h>

void gpio_mode(GPIO_TypeDef *port, uint16_t pins, enum gpio_mode_config cfg)
{
    uint32_t omoder = port->MODER;
    uint8_t offset = 0;

    while (pins) {
        if (pins & 1) {
            MODIFY_REG(omoder, 0b11 << offset, cfg << offset);
        }
        pins >>= 1;
        offset += 2;
    }

    port->MODER = omoder;
}

void gpio_speed(GPIO_TypeDef *port, uint16_t pins, enum gpio_speed_config cfg)
{
    uint32_t ospeedr = port->OSPEEDR;
    uint8_t offset = 0;

    while (pins) {
        if (pins & 1) {
            MODIFY_REG(ospeedr, 0b11 << offset, cfg << offset);
        }
        pins >>= 1;
        offset += 2;
    }

    port->OSPEEDR = ospeedr;
}

void gpio_pupd(GPIO_TypeDef *port, uint16_t pins, enum gpio_pupd_config cfg)
{
    uint32_t pupdr = port->PUPDR;
    uint8_t offset = 0;

    while (pins) {
        if (pins & 1) {
            MODIFY_REG(pupdr, 0b11 << offset, cfg << offset);
        }
        pins >>= 1;
        offset += 2;
    }

    port->PUPDR = pupdr;
}

inline void gpio_push_pull(GPIO_TypeDef *port, uint16_t mask)
{
    port->OTYPER &= ~mask;
}

inline void gpio_open_drain(GPIO_TypeDef *port, uint16_t mask)
{
    port->OTYPER |= mask;
}

inline void gpio_set(GPIO_TypeDef *port, uint16_t mask)
{
    port->BSRR = mask;
}

inline void gpio_clear(GPIO_TypeDef *port, uint16_t mask)
{
    port->BSRR = ((uint32_t) mask) << 16;
}

inline void gpio_write(GPIO_TypeDef *port, uint16_t pin, bool state)
{
    MODIFY_REG(port->ODR, pin, state ? pin : 0);
}

inline void gpio_port_write(GPIO_TypeDef *port, uint16_t mask)
{
    port->ODR = mask;
}

inline void gpio_toggle(GPIO_TypeDef *port, uint16_t mask)
{
    port->ODR ^= mask;
}

inline uint16_t gpio_port_read(GPIO_TypeDef *port)
{
    return port->IDR;
}

inline uint16_t gpio_read(GPIO_TypeDef *port, uint16_t mask)
{
    return port->IDR & mask;
}
