LIBNAME		= libspike
BOOTLOADER	= spikeboot
SRCLIBDIR	= lib
BOOT_INC_RTT	= 1
PREFIX		= arm-none-eabi-
CC		= $(PREFIX)gcc
AR		= $(PREFIX)ar
LD		= $(PREFIX)gcc
OBJCPY		= $(PREFIX)objcopy

TARGET_FLAGS	= -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -DSTM32H723xx

CCFLAGS		= -g3 -ggdb -std=gnu17 -specs=nano.specs -Os \
		  -Wall -Wextra -Wimplicit-function-declaration \
		  -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes \
		  -Wundef -Wshadow \
		  -Iinclude -Ivendor -fno-common \
		  $(TARGET_FLAGS) \
		  -ffunction-sections -fdata-sections -MD

ARFLAGS		= rcs

LDSCRIPT	= spike.ld
LDFLAGS		= -g3 -ggdb -T$(LDSCRIPT) -L. -nostartfiles \
		  $(TARGET_FLAGS) -specs=nano.specs
LDLIBS 		= -lc -lspike

OBJ_DIR		= build

LIB_OBJS	= $(addprefix $(OBJ_DIR)/$(LIBNAME)/, \
		  vector.o gpio.o pwr.o rcc.o syscalls.o syscfg.o nvic.o \
		  irq.o systick.o flash.o usbd.o)

BOOT_OBJS	= $(addprefix $(OBJ_DIR)/$(BOOTLOADER)/, \
		  main.o clock.o com.o)

SEGGER_RTT_FLAG	= -Ivendor/RTT/RTT -Ivendor/RTT/Config
SEGGER_RTT_OBJS	= $(OBJ_DIR)/SEGGER/RTT/SEGGER_RTT.o \
		  $(OBJ_DIR)/SEGGER/Syscalls/SEGGER_RTT_Syscalls_GCC.o

ifeq ($(BOOT_INC_RTT),1)
	BOOT_OBJS += $(SEGGER_RTT_OBJS)
endif


all: $(LIBNAME).a $(BOOTLOADER).bin

include/$(LIBNAME)/irq.h: scripts/cmsis2nvic.py
	@printf "  GEN     irq.h\n"
	@python3 scripts/cmsis2nvic.py > $@

$(LIBNAME).a: $(LIB_OBJS)
	@printf "  AR      $(LIBNAME).a\n"
	@$(AR) $(ARFLAGS) "$@" $(LIB_OBJS)

$(OBJ_DIR)/$(LIBNAME)/%.o: $(SRCLIBDIR)/%.c
	@mkdir -p $(@D)
	@printf "  CC      $(<F)\n"
	@$(CC) $(CCFLAGS) -o $@ -c $<

$(OBJ_DIR)/SEGGER/%.o: vendor/RTT/%.c
	@mkdir -p $(@D)
	@printf "  CC      $(<F)\n"
	@$(CC) $(CCFLAGS) $(SEGGER_RTT_FLAG) -o $@ -c $<

$(OBJ_DIR)/$(BOOTLOADER)/%.o: $(BOOTLOADER)/%.c
	@mkdir -p $(@D)
	@printf "  CC      $(<F)\n"
	@$(CC) $(CCFLAGS) -o $@ -c $<

$(OBJ_DIR)/$(BOOTLOADER)/$(BOOTLOADER).elf: $(BOOT_OBJS) $(LDSCRIPT) $(LIBNAME).a
	@mkdir -p $(@D)
	@printf "  LD      $@\n"
	@$(LD) $(LDFLAGS) -o $@ $(BOOT_OBJS) $(LDLIBS)

$(BOOTLOADER).bin: $(OBJ_DIR)/$(BOOTLOADER)/$(BOOTLOADER).elf
	@printf "  OBJCOPY $@\n"
	@$(OBJCPY) -O binary $< $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(LIBNAME).a
	rm -f $(BOOTLOADER).bin

.PHONY: clean
