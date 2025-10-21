################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/printf.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f30x_temp.c 

OBJS += \
./Src/main.o \
./Src/printf.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f30x_temp.o 

C_DEPS += \
./Src/main.d \
./Src/printf.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f30x_temp.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/printf.cyclo ./Src/printf.d ./Src/printf.o ./Src/printf.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f30x_temp.cyclo ./Src/system_stm32f30x_temp.d ./Src/system_stm32f30x_temp.o ./Src/system_stm32f30x_temp.su

.PHONY: clean-Src

