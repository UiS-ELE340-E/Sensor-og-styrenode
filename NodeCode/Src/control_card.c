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
//#include <metodar/control_card.h>
//---------------------------------------
// Function prototypes
//---------------------------------------
float ymf_past = 0.0f;
float a = 0.0f;					// Filter parameter
float ymf = 0.0f;					// Filter quantity to D-ledd
uint16_t ui_max = 65535;		// Max power from integral
uint16_t u_max = 65535;			// Max power total
uint16_t kp = 4000;				// Proportinal parameter
float Ti = 0.0f;				// Integrator parameter
float Td = 0.01f;					// Derivator parameter
uint32_t yr = 300; //reference;		// Reference
uint8_t blink_test = 0;
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
	data_from_sensor_card();
	data_from_PC();
	PID_calculation();
	LinMot_direction();
	power_delivery();
	construct_data_cc();
	USART2_send_package();

	blink_test++;
	if (blink_test > 9){
		GPIOE->ODR = GPIOE->ODR ^ 0x100;
		blink_test = 0;
	}
}

// Extracting the data from sensor card (UART1)
void data_from_sensor_card(void){	//only taking the distance
	distance = data[2];
	distance = (distance << 8) | data[1];
}


void data_from_PC(void){	//only taking the distance
	uint16_t Td_;
	uint16_t Ti_;
	float Td_f;
	float Ti_f;

	if (USART2_rx_irq > 7){
		yr = USART2_rx[1];
		yr = (yr << 8) | USART2_rx[0];
		kp = USART2_rx[3];
		kp = (kp << 8) | USART2_rx[2];
		Ti_ = USART2_rx[5];
		Ti_ = (Ti_ << 8) | USART2_rx[4];
		Td_ = USART2_rx[7];
		Td_ = (Td_ << 8) | USART2_rx[6];

		Ti_f = Ti_;
		Td_f = Td_;
		Ti = Ti_f / 1000;
		Td = Td_f / 1000;

		USART2_rx_irq = 0;
	}

}


void PID_calculation(void){
	float Tf = (1.0/(2*3.14));		// Time frequancy
	float Ts = 0.01;
	uint32_t ym = distance;			// Actual placement. it will be between 0 and 1500


	error = yr-ym;

	a = Tf/(Tf+Ts);											// Filter parameter

	abs_error = abs(error);
	up = kp*abs_error;											// P-Ledd
	if (up >= u_max){										// I-ledd restriction
		up = u_max;
	}

	if (Ti > 0){
		ui = ui_past + (kp*Ts*(abs_error_past+abs_error))/(Ti*2);	// I-Ledd
	}
	else{
		ui = 0;
	}

	if (ui >= ui_max){										// I-ledd restriction
		ui = ui_max;
	}

	ymf = a*ymf_past+(1-a)*ym;								// Filter for the D-ledd

	ud = -(kp*Td*(ymf-ymf_past))/Ts;						// D-ledd
	if (ud >= u_max){										// I-ledd restriction
		ud = u_max;
	}

	u = up + ui + ud;										// calculating the total power

	abs_error_past = abs_error;

	ui_past = ui;
	ymf_past = ymf;


}



void LinMot_direction(void){	// TIM3 is sending the power to the LinMot and this say if it goes in positive or negative direction
	    if(error < 0){
	    	GPIOB->BSRR = (GPIO_ODR_5 << 16);    // Set PB5 low
	    }
	    else{
	        GPIOB->BSRR = GPIO_ODR_5;			// Set PB5 high
	    }
	}


void power_delivery(void){
    if (abs(error) <= 5)	// If error is smal → stop motor
    {
        TIM3->CCR1 = 0;		// Set PWM to 0
        TIM3->ARR = 0;
        return;   			// Stop function
    }
    if (kp == 0 && Ti == 0 && Td == 0){
        TIM3->CCR1 = 0;		// Set PWM to 0
        TIM3->ARR = 0;
        return;   			// Stop function
    }
    // Begrens u til maks verdi
    power = (u > 65535) ? 65535 : u;

    // Map u (0 → 65532) til frekvens (1k → 250k)
    uint32_t freq = 1000 + (power * (250000 - 1000)) / 65535;

    TIM3_setFrequency(freq);  // Set PSC + ARR automatisk

    // 50 % duty
    uint32_t arr = TIM3->ARR;
    TIM3->CCR1 = (arr + 1) / 2;
}


void TIM3_setFrequency(uint32_t freq_hz)
{
    if (freq_hz < 1000)     freq_hz = 1000;
    if (freq_hz > 250000)   freq_hz = 250000;

    uint32_t timer_clk = 72000000;

    // PSC beregnes matematisk uten loops
    uint32_t psc = (timer_clk + (freq_hz * 65536UL) - 1) / (freq_hz * 65536UL);
    if (psc > 0) psc -= 1;     // Formula give PSC+1, so take away 1


    period = (timer_clk / ((psc + 1) * freq_hz)) - 1;	// Calculating period (ARR)

    // Updating timer
    TIM3->CR1 &= ~TIM_CR1_CEN;     // Stop timer
    TIM3->PSC = psc;
    TIM3->ARR = period;
    TIM3->EGR = TIM_EGR_UG;        // Update shadow
    TIM3->CR1 |= TIM_CR1_CEN;      // Start timer
}


void construct_data_cc(void){

	data_cc[0] = error & 0xFF;
	data_cc[1] = (error >> 8) & 0xFF;
	data_cc[2] = power & 0xFF;
	data_cc[3] = (power >> 8) & 0xFF;
	data_cc[4] = up & 0xFF;
	data_cc[5] = (up >> 8) & 0xFF;
	data_cc[6] = ui & 0xFF;
	data_cc[7] = (ui >> 8) & 0xFF;
	data_cc[8] = ud & 0xFF;
	data_cc[9] = (ud >> 8) & 0xFF;

}






