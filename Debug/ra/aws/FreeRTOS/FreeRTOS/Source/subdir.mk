################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/aws/FreeRTOS/FreeRTOS/Source/event_groups.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/list.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/queue.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/stream_buffer.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/tasks.c \
../ra/aws/FreeRTOS/FreeRTOS/Source/timers.c 

C_DEPS += \
./ra/aws/FreeRTOS/FreeRTOS/Source/event_groups.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/list.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/queue.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/stream_buffer.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/tasks.d \
./ra/aws/FreeRTOS/FreeRTOS/Source/timers.d 

CREF += \
flashware3_eth1.cref 

OBJS += \
./ra/aws/FreeRTOS/FreeRTOS/Source/event_groups.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/list.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/queue.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/stream_buffer.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/tasks.o \
./ra/aws/FreeRTOS/FreeRTOS/Source/timers.o 

MAP += \
flashware3_eth1.map 


# Each subdirectory must supply rules for building sources it contributes
ra/aws/FreeRTOS/FreeRTOS/Source/%.o: ../ra/aws/FreeRTOS/FreeRTOS/Source/%.c
	@echo 'Building file: $<'
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Os -ffunction-sections -fdata-sections -fno-strict-aliasing -fmessage-length=0 -funsigned-char -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Waggregate-return -Wno-parentheses-equality -Wfloat-equal -g3 -std=c99 -fshort-enums -fno-unroll-loops -w -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_gen" -I"." -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_cfg\\fsp_cfg\\bsp" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_cfg\\fsp_cfg" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra_cfg\\aws" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\src" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\inc" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\inc\\api" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\inc\\instances" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\src\\rm_freertos_port" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\aws\\FreeRTOS\\FreeRTOS\\Source\\include" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\arm\\CMSIS_6\\CMSIS\\Core\\Include" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\fsp\\src\\rm_freertos_plus_tcp" -I"C:\\Users\\abdullah.ozdemir\\e2_studio\\workspace\\flashware3_eth1\\ra\\aws\\FreeRTOS\\FreeRTOS-Plus\\Source\\FreeRTOS-Plus-TCP\\source\\include" -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -x c "$<" -c -o "$@")
	@clang --target=arm-none-eabi @"$@.in"

