/*
 * control_card.c
 *
 *  Created on: Nov 6, 2025
 *      Author: STB_UiS
 */

//---------------------------------------
// Inclusions and definitions
//---------------------------------------
#include <metodar/control_card.h>



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
	data_from_sensor_card;
	PID_calculation;
	power_delivery;

}



void PID_calculation(void){
	float a;					// Filter parameter
	float ymf;					// Filter quantity to D-ledd
	float ymf_past = 0;
	float Tf = (1.0/(2*3));		// Time frequancy
	float Ts = Tf/5;
	uint16_t ui_max = 100;
	uint16_t u_max = 100;
	uint8_t kp = 1;				// Proportinal parameter
	uint8_t Ti = 0;				// Integrator parameter
	uint8_t Td = 0;				// Derivator parameter
	uint16_t yr = 5;			// Reference
	uint16_t ym = 2;			// Actual placement


	error = yr-ym;

	a = Tf/(Tf+Ts);											// Filter parameter

	up = kp*error;											// P-Ledd

	ui = ui_past + (kp*Ts*(error-error_past))/(Ti*2);		// I-Ledd
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

	return u;
}

// Calculating the different variables to change TIM3
void power_delivery(void){

	prescalar = 71;				// Gives 1 MHz = 1 us if 71
	period = 0; 				// Needs a frequency at 0-250kHz: 4 gives 250kHz and bigger gives less and less
	puls = (period+1)/2;		// Needs to be half of the period
}



// Extracting the data from sensor card (UART1)
void data_from_sensor_card(void){			// need to make an interrupt
	distance_calculation = IR_sensor_data_mask & distance_calculation;



}






