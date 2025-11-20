/*
 * control_card.c
 *
 *  Created on: Nov 6, 2025
 *      Author: STB_UiS
 */

//---------------------------------------
// Inclusions and definitions
//---------------------------------------

#include <cmsis_boot/stm32f30x.h>
#include "string.h"
#include <extern_dekl_globale_variablar.h>
#include <metodar/control_card.h>
//---------------------------------------
// Function prototypes
//---------------------------------------
void control_card_logic(void);


//---------------------------------------
// Function definitions
//---------------------------------------
/**	@brief	Receives a new measurement of from sensor node. (DMA?)
 * 			Sends the measurements to the superior control system. (DMA?)
 * 			Updates PID variables and sends it to LinMot.
 * 	@param	None
 * 	@retval	None
 */
void control_card_logic(void){
	if (slow_blink > 9){
		GPIOE->ODR = GPIOE->ODR ^ 0x1000;
		slow_blink = 0;
	}
	data_from_sensor_card;
	PID_calculation;
	power_delivery;

}



void PID_calculation(void){
	float a;					// Filter parameter
	float ymf;					// Filter quantity to D-ledd
	float ymf_past = 0;
	float Tf = (1.0/(2*3.14));		// Time frequancy
	float Ts = Tf/5;
	int16_t ui_max = 65535;
	int16_t u_max = 65532;
	float kp = 1;				// Proportinal parameter
	float Ti = 0;				// Integrator parameter
	float Td = 0;				// Derivator parameter
	uint16_t yr = 5;			// Reference
	uint16_t ym = 2;			// Actual placement


	error = yr-ym;
	if (error <= 5){
		error = 0;
	}

	a = Tf/(Tf+Ts);											// Filter parameter

	up = kp*error;											// P-Ledd

	if (Ti == 0){
		ui = 0;
	}
	else{
		ui = ui_past + (kp*Ts*(error-error_past))/(Ti*2);	// I-Ledd
	}
	if (ui >= ui_max){										// I-ledd restriction
		ui = ui_max;
	}

	ymf = a*ymf_past+(1-a)*ym;								// Filter for the D-ledd

	ud = -(kp*Td*(ymf-ymf_past))/Ts;						// D-ledd

	u = up + ui + ud;										// calculating the total power
	if (u >= u_max){										// Power restriction
		u = u_max;
	}

	error_past = error;
	ui_past = ui;
	ymf_past = ymf;

}

// Calculating the different variables to change TIM3
void power_delivery(void){

	prescalar = 71;				// Gives 1 MHz = 1 us if 71
	period = ~u; 				// Needs a frequency at 0-250kHz: 3 gives 250kHz and bigger gives less and less
	puls = (period+1)/2;		// Needs to be half of the period
}



// Extracting the data from sensor card (UART1)
void data_from_sensor_card(void){			// need to make an interrupt
	distance_calculation = IR_sensor_data_mask & distance_calculation;



}






