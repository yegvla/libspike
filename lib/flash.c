#include <stm32h7xx.h>
#include <libspike/flash.h>

void flash_set_latency(enum flash_latency latency)
{
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, latency);
}
