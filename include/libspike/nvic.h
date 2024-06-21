#ifndef LIBSPIKE_NVIC_H
#define LIBSPIKE_NVIC_H

#include <stm32h7xx.h>

enum nvic_priority_group {
    NVIC_PRIORITY_GROUP0 = 0x00000007,
    NVIC_PRIORITY_GROUP1 = 0x00000006,
    NVIC_PRIORITY_GROUP2 = 0x00000005,
    NVIC_PRIORITY_GROUP3 = 0x00000004,
    NVIC_PRIORITY_GROUP4 = 0x00000003,
};

/* Just some wrappers to fit in better with everything else. */

static inline void nvic_set_priority_grouping(enum nvic_priority_group group)
{
    NVIC_SetPriorityGrouping(group);
}

static inline void nvic_set_priority(IRQn_Type irqn, uint32_t prio)
{
    NVIC_SetPriority(irqn, prio);
}

static inline void nvic_enable_irq(IRQn_Type irqn)
{
    NVIC_EnableIRQ(irqn);
}

#endif /* LIBSPIKE_NVIC_H */
