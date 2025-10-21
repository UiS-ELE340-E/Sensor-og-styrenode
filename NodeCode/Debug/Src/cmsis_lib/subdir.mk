################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/cmsis_lib/stm32f30x_adc.c \
../Src/cmsis_lib/stm32f30x_can.c \
../Src/cmsis_lib/stm32f30x_exti.c \
../Src/cmsis_lib/stm32f30x_gpio.c \
../Src/cmsis_lib/stm32f30x_i2c.c \
../Src/cmsis_lib/stm32f30x_it.c \
../Src/cmsis_lib/stm32f30x_misc.c \
../Src/cmsis_lib/stm32f30x_rcc.c \
../Src/cmsis_lib/stm32f30x_spi.c \
../Src/cmsis_lib/stm32f30x_syscfg.c \
../Src/cmsis_lib/stm32f30x_tim.c \
../Src/cmsis_lib/stm32f30x_usart.c 

OBJS += \
./Src/cmsis_lib/stm32f30x_adc.o \
./Src/cmsis_lib/stm32f30x_can.o \
./Src/cmsis_lib/stm32f30x_exti.o \
./Src/cmsis_lib/stm32f30x_gpio.o \
./Src/cmsis_lib/stm32f30x_i2c.o \
./Src/cmsis_lib/stm32f30x_it.o \
./Src/cmsis_lib/stm32f30x_misc.o \
./Src/cmsis_lib/stm32f30x_rcc.o \
./Src/cmsis_lib/stm32f30x_spi.o \
./Src/cmsis_lib/stm32f30x_syscfg.o \
./Src/cmsis_lib/stm32f30x_tim.o \
./Src/cmsis_lib/stm32f30x_usart.o 

C_DEPS += \
./Src/cmsis_lib/stm32f30x_adc.d \
./Src/cmsis_lib/stm32f30x_can.d \
./Src/cmsis_lib/stm32f30x_exti.d \
./Src/cmsis_lib/stm32f30x_gpio.d \
./Src/cmsis_lib/stm32f30x_i2c.d \
./Src/cmsis_lib/stm32f30x_it.d \
./Src/cmsis_lib/stm32f30x_misc.d \
./Src/cmsis_lib/stm32f30x_rcc.d \
./Src/cmsis_lib/stm32f30x_spi.d \
./Src/cmsis_lib/stm32f30x_syscfg.d \
./Src/cmsis_lib/stm32f30x_tim.d \
./Src/cmsis_lib/stm32f30x_usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/cmsis_lib/%.o Src/cmsis_lib/%.su Src/cmsis_lib/%.cyclo: ../Src/cmsis_lib/%.c Src/cmsis_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-cmsis_lib

clean-Src-2f-cmsis_lib:
	-$(RM) ./Src/cmsis_lib/stm32f30x_adc.cyclo ./Src/cmsis_lib/stm32f30x_adc.d ./Src/cmsis_lib/stm32f30x_adc.o ./Src/cmsis_lib/stm32f30x_adc.su ./Src/cmsis_lib/stm32f30x_can.cyclo ./Src/cmsis_lib/stm32f30x_can.d ./Src/cmsis_lib/stm32f30x_can.o ./Src/cmsis_lib/stm32f30x_can.su ./Src/cmsis_lib/stm32f30x_exti.cyclo ./Src/cmsis_lib/stm32f30x_exti.d ./Src/cmsis_lib/stm32f30x_exti.o ./Src/cmsis_lib/stm32f30x_exti.su ./Src/cmsis_lib/stm32f30x_gpio.cyclo ./Src/cmsis_lib/stm32f30x_gpio.d ./Src/cmsis_lib/stm32f30x_gpio.o ./Src/cmsis_lib/stm32f30x_gpio.su ./Src/cmsis_lib/stm32f30x_i2c.cyclo ./Src/cmsis_lib/stm32f30x_i2c.d ./Src/cmsis_lib/stm32f30x_i2c.o ./Src/cmsis_lib/stm32f30x_i2c.su ./Src/cmsis_lib/stm32f30x_it.cyclo ./Src/cmsis_lib/stm32f30x_it.d ./Src/cmsis_lib/stm32f30x_it.o ./Src/cmsis_lib/stm32f30x_it.su ./Src/cmsis_lib/stm32f30x_misc.cyclo ./Src/cmsis_lib/stm32f30x_misc.d ./Src/cmsis_lib/stm32f30x_misc.o ./Src/cmsis_lib/stm32f30x_misc.su ./Src/cmsis_lib/stm32f30x_rcc.cyclo ./Src/cmsis_lib/stm32f30x_rcc.d ./Src/cmsis_lib/stm32f30x_rcc.o ./Src/cmsis_lib/stm32f30x_rcc.su ./Src/cmsis_lib/stm32f30x_spi.cyclo ./Src/cmsis_lib/stm32f30x_spi.d ./Src/cmsis_lib/stm32f30x_spi.o ./Src/cmsis_lib/stm32f30x_spi.su ./Src/cmsis_lib/stm32f30x_syscfg.cyclo ./Src/cmsis_lib/stm32f30x_syscfg.d ./Src/cmsis_lib/stm32f30x_syscfg.o ./Src/cmsis_lib/stm32f30x_syscfg.su ./Src/cmsis_lib/stm32f30x_tim.cyclo ./Src/cmsis_lib/stm32f30x_tim.d ./Src/cmsis_lib/stm32f30x_tim.o ./Src/cmsis_lib/stm32f30x_tim.su ./Src/cmsis_lib/stm32f30x_usart.cyclo ./Src/cmsis_lib/stm32f30x_usart.d ./Src/cmsis_lib/stm32f30x_usart.o ./Src/cmsis_lib/stm32f30x_usart.su

.PHONY: clean-Src-2f-cmsis_lib

