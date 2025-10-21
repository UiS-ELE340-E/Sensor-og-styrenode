################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/example/GPIO_Toggle_Example.c \
../Src/example/system_stm32f30x.c 

OBJS += \
./Src/example/GPIO_Toggle_Example.o \
./Src/example/system_stm32f30x.o 

C_DEPS += \
./Src/example/GPIO_Toggle_Example.d \
./Src/example/system_stm32f30x.d 


# Each subdirectory must supply rules for building sources it contributes
Src/example/%.o Src/example/%.su Src/example/%.cyclo: ../Src/example/%.c Src/example/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-example

clean-Src-2f-example:
	-$(RM) ./Src/example/GPIO_Toggle_Example.cyclo ./Src/example/GPIO_Toggle_Example.d ./Src/example/GPIO_Toggle_Example.o ./Src/example/GPIO_Toggle_Example.su ./Src/example/system_stm32f30x.cyclo ./Src/example/system_stm32f30x.d ./Src/example/system_stm32f30x.o ./Src/example/system_stm32f30x.su

.PHONY: clean-Src-2f-example

