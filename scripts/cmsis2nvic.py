#/usr/bin/env python3

import sys
import os
from dataclasses import dataclass

try:
    os.remove("include/libspike/irq.h")
    os.remove("lib/irq.c")
except OSError:
    pass

irq_h = open("include/libspike/irq.h", "a")
irq_c = open("lib/irq.c", "a")

@dataclass
class IRQDef:
    name: str
    num: int

cmsis = sys.argv[1]

record = False
defs = []

with open(cmsis, 'r') as fp:
    for line in fp:
        if "IRQn_Type" in line:
            break

        if record:
            line = line.strip()
            dec = line.split("=")
            isr_name = dec[0].strip().lower().replace("_irqn", "")
            num = int(dec[1].split(",")[0].strip())
            defs.append(IRQDef(isr_name, num))
        
        if "STM32 specific Interrupt Numbers" in line:
            record = True
        
if not record:
    print("#error \"Could not find Interrupt Numbers enum in CMSIS file.\"", file=irq_h)
    exit(1)

print("#include <libspike/irq.h>", file=irq_c)
print("#include <libspike/vector.h>\n", file=irq_c)

print("""
void blocking_handler(void)
{
    while (1);
}

void nop_handler(void)
{
    /* NOP */
}

void nmi_handler(void) __attribute__((weak, alias("nop_handler")));
void hard_fault_handler(void) __attribute__((weak, alias("blocking_handler")));
void memory_manage_fault_handler(void) __attribute__((weak, alias("blocking_handler")));
void bus_fault_handler(void) __attribute__((weak, alias("blocking_handler")));
void usage_fault_handler(void) __attribute__((weak, alias("blocking_handler")));
void sv_call_handler(void) __attribute__((weak, alias("nop_handler")));
void debug_monitor_handler(void) __attribute__((weak, alias("nop_handler")));
void pend_sv_handler(void) __attribute__((weak, alias("nop_handler")));
void systick_handler(void) __attribute__((weak, alias("nop_handler")));
""", file=irq_c)

print("#ifndef LIBSPIKE_IRQ_H", file=irq_h)
print("#define LIBSPIKE_IRQ_H", file=irq_h)
    
# Generate prototypes
for irq in defs:
    print(f"void {irq.name}_isr(void);", file=irq_h)
    print(f"void {irq.name}_isr(void) __attribute__((weak, alias(\"blocking_handler\")));", file=irq_c)

print("", file=irq_h)

count = 0

for irq in defs:
    if irq.num > count:
        count = irq.num

count += 1

# Generate vector table
print(f"#define VECTOR_IRQ_COUNT {count}", file=irq_h)
print(f"#define VECTOR_IRQ_LIST {{ \\", file=irq_h)
for irq in defs:
    print(f"    [{irq.num}] = {irq.name}_isr, \\", file=irq_h)
print("}", file=irq_h)

print("#endif  /* define LIBSPIKE_IRQ_H */", file=irq_h)

irq_h.close()
irq_c.close()
