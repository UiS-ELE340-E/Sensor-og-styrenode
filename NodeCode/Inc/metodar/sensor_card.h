/*
 * sensor_card.h
 *
 *  Created on: Nov 6, 2025
 *      Author: STB_UiS
 */

#ifndef METODAR_SENSOR_CARD_H_
#define METODAR_SENSOR_CARD_H_

//---------------------------------------
// Inclusions and definitions
//---------------------------------------
#include <cmsis_lib/stm32f30x_adc.h>
#include <cmsis_lib/stm32f30x_dma.h>
#include "string.h"
#include <extern_dekl_globale_variablar.h>
//#include "stm32f3_discovery/stm32f3_discovery_lsm303dlhc.h"

//---------------------------------------
// Function prototypes
//---------------------------------------
void sensor_card_logic(void);
void get_accelerometerdata(void);
uint16_t convert_sensordata(void);
void construct_data(void);
void send_data(void);

#endif /* METODAR_SENSOR_CARD_H_ */
