#include "stm32h723xx.h"
#include "stm32h7xx.h"
#include <libspike/pwr.h>
#include <libspike/utils.h>

inline void pwr_set_supply_config(enum pwr_supply_config cnf)
{
    MODIFY_REG(PWR->CR3, 0b111111, cnf);
}

inline void pwr_ldo_supply(void)
{
    pwr_set_supply_config(PWR_SUPPLY_LDO);
}

inline void pwr_direct_smps(void)
{
    pwr_set_supply_config(PWR_SUPPLY_DIRECT_SMPS);
}

inline void pwr_smps_feeds_ldo(void)
{
    pwr_set_supply_config(PWR_SUPPLY_SMPS_FEED_LDO);
}

inline void pwr_smps_feeds_ext_and_ldo(void)
{
    pwr_set_supply_config(PWR_SUPPLY_SMPS_FEED_EXTERNAL_LDO);
}

inline void pwr_voltage_scaling(enum pwr_voltage_scaling scale)
{
    reg32_t dummy = 0;
    MODIFY_REG(PWR->D3CR, PWR_D3CR_VOS, scale << PWR_D3CR_VOS_Pos);
    dummy = READ_BIT(PWR->D3CR, PWR_D3CR_VOS);
    (void)dummy;
}

inline void pwr_enable_bkup_accesss(void)
{
    PWR->CR1 |= PWR_CR1_DBP;
}

inline void pwr_disable_bkup_accesss(void)
{
    PWR->CR1 &= ~PWR_CR1_DBP;
}
