//
// File: initialisering.c
// m.t.160913
//---------------------------------------

//---------------------------------------
// Inclusions and definitions
//---------------------------------------
#include <cmsis_boot/stm32f30x.h>
#include <cmsis_lib/stm32f30x_adc.h>
#include <extern_dekl_globale_variablar.h>
#include <metodar/UART_metodar.h>
#include <metodar/TIM_metodar.h>
#include <cmsis_lib/stm32f30x_spi.h>

//---------------------------------------
// Function prototypes
//---------------------------------------
void init(void);
void enable(uint8_t node);
uint8_t control_or_sensor(void);
uint8_t cable_or_BLT(void);
void set_LED(uint8_t status);

void GPIO_oppstart(void);
void SysTick_init(uint32_t hz);
void LinMot_oppstart(void);
void aks_oppstart(void);
void interrupt_init(void);
void ADC3_init(void);
void PB5_init(void);
void SPI2_oppstart(void);
void Exp_click_sokkel1_oppstart(void);

//---------------------------------------
// Function definitions
//---------------------------------------
void init(void) {
	GPIO_oppstart();

	set_LED(8);

	SPI2_oppstart();
	Exp_click_sokkel1_oppstart();
	aks_oppstart();
	USART1_init();
	USART2_init();
 	USART3_init();
	TIM2_init();
	TIM3_init();
	TIM4_init();
	PB5_init();
	ADC3_init();
	SysTick_init(1000);
	interrupt_init();

	// Check node type
    node = control_or_sensor();
    // Check communication type
    communication = cable_or_BLT();
    // Enable node specific peripherals
    enable(node);
}

uint8_t control_or_sensor(void){
	// Start ADC conversion
	ADC_StartConversion(ADC3);

	// Wait until conversion is complete
	while (ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC) == RESET);

	// Read the converted value
	sensor_data = ADC_GetConversionValue(ADC3);

	if (sensor_data < 50){
		// Control node
		return 0;
	}
	else{
		// Sensor node
		return 1;
	}
}

uint8_t cable_or_BLT(void){
	// Test communication
	// Now always set to cable
	uint8_t com = 0;

	if (com == 0){
		// Cable communication
		return 0;
	}
	else{
		// BLT communication
		return 1;
	}
}

void enable(uint8_t node){
	if (node == 0){
		// Control node
		ADC_Cmd(ADC3, DISABLE);
		TIM_Cmd(TIM2, DISABLE);
		TIM_Cmd(TIM4, DISABLE);
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	}
	else if (node == 1){
		// Sensor node
		TIM_Cmd(TIM2, DISABLE);
		TIM_Cmd(TIM3, DISABLE);
		USART_Cmd(USART2, DISABLE);
		SysTick_init(100);
	}
	if (communication == 0){
		USART3_DMA_init(node);
		USART3_DMA_enable(node);
	}
	else{
		USART1_DMA_enable(node);
	}
	set_LED(node);
}

void set_LED(uint8_t status){
	if (status == 0) {
		GPIOE->ODR = GPIOE->ODR ^ 0x0400;
		GPIOE->ODR = GPIOE->ODR ^ 0x0800;
		GPIOE->ODR = GPIOE->ODR ^ 0x1000;
		GPIOE->ODR = GPIOE->ODR ^ 0x4000;
		GPIOE->ODR = GPIOE->ODR ^ 0x8000;
		GPIOE->ODR = GPIOE->ODR ^ 0x0100;
	}
	else if (status == 1) {
		GPIOE->ODR = GPIOE->ODR ^ 0x0200;
		GPIOE->ODR = GPIOE->ODR ^ 0x0400;
		GPIOE->ODR = GPIOE->ODR ^ 0x1000;
		GPIOE->ODR = GPIOE->ODR ^ 0x2000;
		GPIOE->ODR = GPIOE->ODR ^ 0x4000;
		GPIOE->ODR = GPIOE->ODR ^ 0x0100;
	}
	else{
		GPIOE->ODR = GPIOE->ODR ^ 0x0200;
		GPIOE->ODR = GPIOE->ODR ^ 0x0400;
		GPIOE->ODR = GPIOE->ODR ^ 0x0800;
		GPIOE->ODR = GPIOE->ODR ^ 0x1000;
		GPIOE->ODR = GPIOE->ODR ^ 0x2000;
		GPIOE->ODR = GPIOE->ODR ^ 0x4000;
		GPIOE->ODR = GPIOE->ODR ^ 0x8000;
		GPIOE->ODR = GPIOE->ODR ^ 0x0100;
	}
}
