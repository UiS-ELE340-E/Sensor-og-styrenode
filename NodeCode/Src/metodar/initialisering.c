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

//#include <stm32f3_discovery/stm32f3_discovery_lsm303dlhc.h>


//---------------------------------------
// Function prototypes
//---------------------------------------
void init(void);
void enable(uint8_t node);
uint8_t control_or_sensor(void);

void GPIO_oppstart(void);
void SysTick_init(uint32_t hz);
void USART1_init(void);
void USART2_init(void);
void USART3_init(void);
void TIM2_oppstart(void);
void SPI1_oppstart(void);
void SPI2_oppstart(void);
void Exp_click_sokkel1_oppstart(void);
void LinMot_oppstart(void);
void aks_oppstart(void);
void gyro_oppstart(void);
void interrupt_init(void);

//---------------------------------------
// Function definitions
//---------------------------------------
void init(void) {
	GPIO_oppstart();
	SPI1_oppstart();
	SPI2_oppstart();
	Exp_click_sokkel1_oppstart();
	aks_oppstart();
	gyro_oppstart();
	USART1_init();
	USART2_init();
 	USART3_init();
	TIM2_oppstart();
	SysTick_init(1000);
	interrupt_init();

	// Check node type
    node = control_or_sensor();
    // Enable node specific peripherals
    enable(node);

}

uint8_t control_or_sensor(void){
	sensor_data = ADC_GetConversionValue(ADC3);

	if (sensor_data == 0){
		ADC_Cmd(ADC3, DISABLE);
		return 0;
	}
	else{
		return 1;
	}
}

void enable(uint8_t node){
	if (node == 0){

	}
	else if (node == 1){

	}
}
