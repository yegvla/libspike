#ifndef LIBSPIKE_POWER_H
#define LIBSPIKE_POWER_H

#include <stm32h7xx.h>
#include <stdbool.h>

/* This should be done via the bitmaps provided by the CMSIS header
 * instead of just writing out the number in binary representation,
 * but for what ever reason, I cannot find complete definitions for
 * the fields in question... */
enum pwr_supply_config {
    PWR_SUPPLY_LDO =                    0b000010,
    PWR_SUPPLY_DIRECT_SMPS =            0b000100,
    PWR_SUPPLY_SMPS_FEED_LDO =          0b100110,
    PWR_SUPPLY_SMPS_FEED_EXTERNAL_LDO = 0b101110,
                                      /*  ||||||_ BYPASS
                                       *  |||||__ LDOEN
                                       *  ||||___ SDEN
                                       *  |||____ SDEXTHP
                                       *  ||_____ SDLEVEL0
                                       *  |______ SDLEVEL1 */
};

enum pwr_voltage_scaling {
    PWR_VOLTAGE_SCALE0 = 0b00,  /* 1.25V - 1.35V */
    PWR_VOLTAGE_SCALE3 = 0b01,  /* 1.15V - 1.25V */
    PWR_VOLTAGE_SCALE2 = 0b10,  /* 1.05V - 1.15V */
    PWR_VOLTAGE_SCALE1 = 0b11,  /* 0.95V - 1.05V */
};

void pwr_set_supply_config(enum pwr_supply_config);
void pwr_ldo_supply(void);
void pwr_direct_smps(void);
void pwr_smps_feeds_ldo(void);
void pwr_smps_feeds_ext_and_ldo(void);
void pwr_voltage_scaling(enum pwr_voltage_scaling scale);
void pwr_enable_bkup_accesss(void);
void pwr_disable_bkup_accesss(void);

#endif /* LIBSPIKE_POWER_H */
