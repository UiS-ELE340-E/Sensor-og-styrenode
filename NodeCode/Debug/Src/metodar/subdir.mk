################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/metodar/ADC_metodar.c \
../Src/metodar/GPIO_metodar.c \
../Src/metodar/I2C_metodar.c \
../Src/metodar/LCD_metodar.c \
../Src/metodar/LSM303DLHC_metodar.c \
../Src/metodar/SPI1_metodar.c \
../Src/metodar/SPI2_metodar.c \
../Src/metodar/TIM_metodar.c \
../Src/metodar/UART_metodar.c \
../Src/metodar/avbrots_metodar.c \
../Src/metodar/initialisering.c 

OBJS += \
./Src/metodar/ADC_metodar.o \
./Src/metodar/GPIO_metodar.o \
./Src/metodar/I2C_metodar.o \
./Src/metodar/LCD_metodar.o \
./Src/metodar/LSM303DLHC_metodar.o \
./Src/metodar/SPI1_metodar.o \
./Src/metodar/SPI2_metodar.o \
./Src/metodar/TIM_metodar.o \
./Src/metodar/UART_metodar.o \
./Src/metodar/avbrots_metodar.o \
./Src/metodar/initialisering.o 

C_DEPS += \
./Src/metodar/ADC_metodar.d \
./Src/metodar/GPIO_metodar.d \
./Src/metodar/I2C_metodar.d \
./Src/metodar/LCD_metodar.d \
./Src/metodar/LSM303DLHC_metodar.d \
./Src/metodar/SPI1_metodar.d \
./Src/metodar/SPI2_metodar.d \
./Src/metodar/TIM_metodar.d \
./Src/metodar/UART_metodar.d \
./Src/metodar/avbrots_metodar.d \
./Src/metodar/initialisering.d 


# Each subdirectory must supply rules for building sources it contributes
Src/metodar/%.o Src/metodar/%.su Src/metodar/%.cyclo: ../Src/metodar/%.c Src/metodar/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-metodar

clean-Src-2f-metodar:
	-$(RM) ./Src/metodar/ADC_metodar.cyclo ./Src/metodar/ADC_metodar.d ./Src/metodar/ADC_metodar.o ./Src/metodar/ADC_metodar.su ./Src/metodar/GPIO_metodar.cyclo ./Src/metodar/GPIO_metodar.d ./Src/metodar/GPIO_metodar.o ./Src/metodar/GPIO_metodar.su ./Src/metodar/I2C_metodar.cyclo ./Src/metodar/I2C_metodar.d ./Src/metodar/I2C_metodar.o ./Src/metodar/I2C_metodar.su ./Src/metodar/LCD_metodar.cyclo ./Src/metodar/LCD_metodar.d ./Src/metodar/LCD_metodar.o ./Src/metodar/LCD_metodar.su ./Src/metodar/LSM303DLHC_metodar.cyclo ./Src/metodar/LSM303DLHC_metodar.d ./Src/metodar/LSM303DLHC_metodar.o ./Src/metodar/LSM303DLHC_metodar.su ./Src/metodar/SPI1_metodar.cyclo ./Src/metodar/SPI1_metodar.d ./Src/metodar/SPI1_metodar.o ./Src/metodar/SPI1_metodar.su ./Src/metodar/SPI2_metodar.cyclo ./Src/metodar/SPI2_metodar.d ./Src/metodar/SPI2_metodar.o ./Src/metodar/SPI2_metodar.su ./Src/metodar/TIM_metodar.cyclo ./Src/metodar/TIM_metodar.d ./Src/metodar/TIM_metodar.o ./Src/metodar/TIM_metodar.su ./Src/metodar/UART_metodar.cyclo ./Src/metodar/UART_metodar.d ./Src/metodar/UART_metodar.o ./Src/metodar/UART_metodar.su ./Src/metodar/avbrots_metodar.cyclo ./Src/metodar/avbrots_metodar.d ./Src/metodar/avbrots_metodar.o ./Src/metodar/avbrots_metodar.su ./Src/metodar/initialisering.cyclo ./Src/metodar/initialisering.d ./Src/metodar/initialisering.o ./Src/metodar/initialisering.su

.PHONY: clean-Src-2f-metodar

