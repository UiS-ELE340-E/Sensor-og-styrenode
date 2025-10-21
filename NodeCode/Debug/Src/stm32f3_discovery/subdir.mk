################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/stm32f3_discovery/stm32f3_discovery.c \
../Src/stm32f3_discovery/stm32f3_discovery_l3gd20.c \
../Src/stm32f3_discovery/stm32f3_discovery_lsm303dlhc.c 

OBJS += \
./Src/stm32f3_discovery/stm32f3_discovery.o \
./Src/stm32f3_discovery/stm32f3_discovery_l3gd20.o \
./Src/stm32f3_discovery/stm32f3_discovery_lsm303dlhc.o 

C_DEPS += \
./Src/stm32f3_discovery/stm32f3_discovery.d \
./Src/stm32f3_discovery/stm32f3_discovery_l3gd20.d \
./Src/stm32f3_discovery/stm32f3_discovery_lsm303dlhc.d 


# Each subdirectory must supply rules for building sources it contributes
Src/stm32f3_discovery/%.o Src/stm32f3_discovery/%.su Src/stm32f3_discovery/%.cyclo: ../Src/stm32f3_discovery/%.c Src/stm32f3_discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-stm32f3_discovery

clean-Src-2f-stm32f3_discovery:
	-$(RM) ./Src/stm32f3_discovery/stm32f3_discovery.cyclo ./Src/stm32f3_discovery/stm32f3_discovery.d ./Src/stm32f3_discovery/stm32f3_discovery.o ./Src/stm32f3_discovery/stm32f3_discovery.su ./Src/stm32f3_discovery/stm32f3_discovery_l3gd20.cyclo ./Src/stm32f3_discovery/stm32f3_discovery_l3gd20.d ./Src/stm32f3_discovery/stm32f3_discovery_l3gd20.o ./Src/stm32f3_discovery/stm32f3_discovery_l3gd20.su ./Src/stm32f3_discovery/stm32f3_discovery_lsm303dlhc.cyclo ./Src/stm32f3_discovery/stm32f3_discovery_lsm303dlhc.d ./Src/stm32f3_discovery/stm32f3_discovery_lsm303dlhc.o ./Src/stm32f3_discovery/stm32f3_discovery_lsm303dlhc.su

.PHONY: clean-Src-2f-stm32f3_discovery

