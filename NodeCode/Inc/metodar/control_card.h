/*
 * control_card.h
 *
 *  Created on: Nov 6, 2025
 *      Author: Tormo
 */

#ifndef METODAR_CONTROL_CARD_H_
#define METODAR_CONTROL_CARD_H_

//---------------------------------------
// Inclusions and definitions
//---------------------------------------
#include <cmsis_lib/stm32f30x_adc.h>
#include <cmsis_lib/stm32f30x_dma.h>
#include <extern_dekl_globale_variablar.h>
#include <math.h>
#include <stdlib.h>

//---------------------------------------
// Function prototypes
//---------------------------------------
void control_card_logic(void);
void PID_calculation(void);
void TIM3_setFrequency(uint32_t freq_hz);
void power_delivery(void);
void data_from_sensor_card(void);
void data_from_PC(void);
void LinMot_direction(void);
void construct_data_cc(void);
void USART2_send_package(void);

#endif /* METODAR_CONTROL_CARD_H_ */
