/*
 * TIM_metodar.h
 *
 *  Created on: Nov 6, 2025
 *      Author: STB_UiS
 */

#ifndef METODAR_TIM_METODAR_H_
#define METODAR_TIM_METODAR_H_

//---------------------------------------
// Inclusions and definitions
//---------------------------------------
#include <cmsis_boot/stm32f30x.h>
#include <cmsis_lib/stm32f30x_gpio.h>
#include <cmsis_lib/stm32f30x_rcc.h>
#include <cmsis_lib/stm32f30x_tim.h>
#include <extern_dekl_globale_variablar.h>

//---------------------------------------
// Function prototypes
//---------------------------------------
void TIM2_init(void);
void PWM_sett_vidde_TIM2_CH2(uint32_t vidde);
void TIM4_init(void);
void TIM4_deactivate(void);

#endif /* METODAR_TIM_METODAR_H_ */
