################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/fsp/src/r_ether_phy/targets/DP83620/r_ether_phy_target_dp83620.c 

C_DEPS += \
./ra/fsp/src/r_ether_phy/targets/DP83620/r_ether_phy_target_dp83620.d 

CREF += \
flashware3_eth1.cref 

OBJS += \
./ra/fsp/src/r_ether_phy/targets/DP83620/r_ether_phy_target_dp83620.o 

MAP += \
flashware3_eth1.map 


# Each subdirectory must supply rules for building sources it contributes
ra/fsp/src/r_ether_phy/targets/DP83620/%.o: ../ra/fsp/src/r_ether_phy/targets/DP83620/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -fshort-enums -fno-unroll-loops -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_gen" -I"." -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_cfg\\fsp_cfg" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_cfg\\aws" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\src" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\inc" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\inc\\api" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\inc\\instances" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\src\\rm_freertos_port" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\aws\\FreeRTOS\\FreeRTOS\\Source\\include" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\src\\rm_freertos_plus_tcp" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\aws\\FreeRTOS\\FreeRTOS-Plus\\Source\\FreeRTOS-Plus-TCP\\source\\include" -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

