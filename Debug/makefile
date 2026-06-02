################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

-include makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include ra_gen/subdir.mk
-include ra/fsp/src/rm_freertos_port/subdir.mk
-include ra/fsp/src/rm_freertos_plus_tcp/subdir.mk
-include ra/fsp/src/r_ioport/subdir.mk
-include ra/fsp/src/r_ether_phy/targets/KSZ8091RNB/subdir.mk
-include ra/fsp/src/r_ether_phy/targets/KSZ8041/subdir.mk
-include ra/fsp/src/r_ether_phy/targets/ICS1894/subdir.mk
-include ra/fsp/src/r_ether_phy/targets/DP83620/subdir.mk
-include ra/fsp/src/r_ether_phy/subdir.mk
-include ra/fsp/src/r_ether/subdir.mk
-include ra/fsp/src/bsp/mcu/ra6m2/subdir.mk
-include ra/fsp/src/bsp/mcu/all/subdir.mk
-include ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/subdir.mk
-include ra/aws/FreeRTOS/FreeRTOS/Source/portable/MemMang/subdir.mk
-include ra/aws/FreeRTOS/FreeRTOS/Source/subdir.mk
-include ra/aws/FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-TCP/source/portable/BufferManagement/subdir.mk
-include ra/aws/FreeRTOS/FreeRTOS-Plus/Source/FreeRTOS-Plus-TCP/source/subdir.mk
-include ra/arm/CMSIS_6/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(P_UPPER_DEPS)),)
-include $(P_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(PP_UPPER_DEPS)),)
-include $(PP_UPPER_DEPS)
endif
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif
ifneq ($(strip $(FSY_UPPER_DEPS)),)
-include $(FSY_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
$(C_DEPS):$(SMS_ASM)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(JMP_UPPER_DEPS)),)
-include $(JMP_UPPER_DEPS)
endif
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_UPPER_DEPS)),)
-include $(SX_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
OBJCOPY += \
flashware3_eth1.srec \

SECONDARY_SIZE += \
flashware3_eth1.siz \


# All Target
all: flashware3_eth1.elf secondary-outputs

# Tool invocations
flashware3_eth1.elf: $(OBJS) $(USER_OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(LINKER_SCRIPT)
	$(file > flashware3_eth1.elf.in,-mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -o "flashware3_eth1.elf" $(OBJS) $(USER_OBJS) -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_gen" -I"." -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_cfg\\fsp_cfg" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_cfg\\aws" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\src" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\inc" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\inc\\api" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\inc\\instances" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\src\\rm_freertos_port" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\aws\\FreeRTOS\\FreeRTOS\\Source\\include" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\src\\rm_freertos_plus_tcp" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\aws\\FreeRTOS\\FreeRTOS-Plus\\Source\\FreeRTOS-Plus-TCP\\source\\include" -T "fsp.lld" -L"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1/script" -L"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\Debug" -Wl,-Map=flashware3_eth1.map -Wl,--start-group -lcrt0 -lc++abi  -Wl,--end-group -Wl,--gc-sections -Wl,--cref -Wl,-z,norelro -Wl,--icf=none)
	@echo Building target: $@ && clang  --target=arm-none-eabi @"flashware3_eth1.elf.in"> flashware3_eth1.cref
flashware3_eth1.srec: flashware3_eth1.elf
	llvm-objcopy "flashware3_eth1.elf" -O srec  "flashware3_eth1.srec"
flashware3_eth1.siz: flashware3_eth1.elf
	llvm-size --format=berkeley "flashware3_eth1.elf"
# Other Targets
clean:
	-$(file > clean_file.tmp,  $(JMP_DEPS)  $(FSY_DEPS)  $(C_UPPER_DEPS)  $(SECONDARY_SIZE)  $(SRC_UPPER_DEPS)  $(P_UPPER_DEPS)  $(S_DEPS)  $(PP_UPPER_DEPS)  $(P_DEPS)  $(FSY_UPPER_DEPS)  $(C_DEPS)  $(CREF)  $(SRC_DEPS)  $(OBJCOPY)  $(JMP_UPPER_DEPS)  $(PP_DEPS)  $(SX_DEPS)  $(ASM_UPPER_DEPS)  $(OBJS)  $(SX_UPPER_DEPS)  $(ASM_DEPS)  $(MAP)  $(S_UPPER_DEPS) )
	-@ xargs -P 2 -s 32000 -t -a clean_file.tmp $(RM)
	-@$(RM) clean_file.tmp
	-$(RM)  flashware3_eth1.elf
	-@echo ' '

secondary-outputs: $(OBJCOPY) $(SECONDARY_SIZE)

.PHONY: all clean dependents 

-include ../makefile.targets
