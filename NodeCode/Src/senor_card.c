/*
 * senor_card.c
 *
 *  Created on: Nov 6, 2025
 *      Author: STB_UiS
 */

//---------------------------------------
// Inclusions and definitions
//---------------------------------------
#include <cmsis_lib/stm32f30x_adc.h>
#include <cmsis_lib/stm32f30x_dma.h>
#include "string.h"
#include <extern_dekl_globale_variablar.h>
#include "stm32f3_discovery/stm32f3_discovery_lsm303dlhc.h"

//---------------------------------------
// Function prototypes
//---------------------------------------
void sensor_card_logic(void);
void get_accelerometerdata(void);
uint16_t convert_sensordata(void);
void construct_data(void);
void send_data(void);

//---------------------------------------
// Function definitions
//---------------------------------------
/**	@brief	Takes a new measurement of distance and acceleration.
 * 			Then sends the measurement to the control node.
 * 	@param	None
 * 	@retval	None
 */
void sensor_card_logic(void){
	sample_time++;
	get_accelerometerdata();
	sensor_data = ADC_GetConversionValue(ADC3);
	distance = convert_sensordata();
	construct_data();
	send_data();
}

void get_accelerometerdata(void){
	uint16_t a;

	// OUT_X_L_A is stored on the lowest address in XYZ-register in the circuit
	LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_X_L_A, buffer, 6);

	// Build accelerometer data.
	/* Buffer 1 is MSByte (from data sheet). Make the relevant 12 bits into integer.
	 * This gives the interval [-2048,2047]. The resolution is 1 mG per LSb
	 * with +/-2 G area in accordance to the data sheet. The value 1000 is 1 G.
	 */
	a   = (buffer[1] << 8) | buffer[0];
	a_x = ((int16_t)(a)) >> 4;
	a   = (buffer[3] << 8) | buffer[2];
	a_y = ((int16_t)(a)) >> 4;
	a   = (buffer[5] << 8) | buffer[4];
	a_z = ((int16_t)(a)) >> 4;

	// Filter the measurements
	/*
	 * Using aliasing filter.
	 * See the deceleration file.
	 */
	a_xf_k = (a1*a_xf_k_1 + b1*a_x)/100;
	a_xf_k_1 = a_xf_k;

	a_yf_k = (a1*a_yf_k_1 + b1*a_y)/100;
	a_yf_k_1 = a_yf_k;

	a_zf_k = (a1*a_zf_k_1 + b1*a_z)/100;
	a_zf_k_1 = a_zf_k;
}

uint16_t convert_sensordata(void){
	uint16_t dist = (3000 * sensor_data) / 4096;

	return dist;
}

void construct_data(void){
	/*
	data[0] = xxx;
	data[1] = xxx;
	data[2] = xxx;
	data[3] = xxx;
	data[4] = xxx;
	data[5] = xxx;
	data[6] = xxx;
	data[7] = xxx;
	data[8] = xxx;
	data[9] = xxx;
	*/
}

void send_data(void){

	// 1️. Copy the payload into the static buffer
	// Fast RAM to RAM copy
	memcpy(transmit_buffer, data, buffer_size);

	// 2️. Make sure the DMA channel is idle
	DMA_Cmd(DMA1_Channel2, DISABLE);
	// Wait for disable
	while (DMA_GetITStatus(DMA1_IT_GL2)) __NOP;

	// 3️. Tell the DMA how many bytes to move this time
	// DMA1_Channel2->CNDTR = buffer_size;

	// 4️. (Re)enable the channel – the transfer starts immediately
	DMA_Cmd(DMA1_Channel2, ENABLE);

	return;
}
