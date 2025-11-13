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
// Function prototypes
//---------------------------------------
void control_card_logic(void);
void power_delivery(void);
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

}

// Calculating the different variables to change TIM3
void power_delivery(void){

	prescalar = 71;				// Gives 1 MHz = 1 us if 71
	period = 0; 				// Needs a frequency at 0-250kHz: 4 gives 250kHz and bigger gives less and less
	puls = (period+1)/2;		// Needs to be half of the period
}
