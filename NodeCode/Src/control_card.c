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
float ymf_past = 0.0f;
float a = 0.0f;					// Filter parameter
float ymf = 0.0f;					// Filter quantity to D-ledd
int32_t u_max = 65535;			// Max power
int32_t u_min = -65535;
int16_t kp = 1200;				// Proportinal parameter
float Ti = 1.0f;				// Integrator parameter
float Td = 0.012f;					// Derivator parameter
uint32_t yr = 300; //reference;		// Reference
uint8_t blink_test = 0;
uint32_t timer_clk = 72000000;
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

void data_from_PC(void){
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
	if (abs_error > 4)  up = kp*error;						// P-Ledd
	else{
		up = 0;
	}

	if (Ti > 0 && abs_error > 4){
		ui = ui_past + (kp*Ts*(error_past+error))/(Ti*2);	// I-Ledd
	}
	else{
		ui = 0;
	}
	if (ui > u_max)	ui = u_max;						// I-ledd restriction
	if (ui < u_min)	ui = u_min;

	ymf = a*ymf_past+(1-a)*ym;								// Filter for the D-ledd

	if (Td > 0 && abs_error > 4){
		ud = -(kp*Td*(ymf-ymf_past))/Ts;			// D-ledd
	}
	else{
		ud = 0;
	}
	if (ud > u_max)	ud = u_max;						// D-ledd restriction
	if (ud < u_min)	ud = u_min;

	u = abs(up + ui + ud);										// calculating the total power

	error_past = error;
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
    if (abs(error) <= 4){	// If error is smal → stop motor
        TIM3->CCR1 = 0;		// Set PWM to 0
        TIM3->ARR = 0;
        power = 0;
        return;   			// Stop function
    }
    if (kp == 0 && Ti == 0 && Td == 0){
        TIM3->CCR1 = 0;		// Set PWM to 0
        TIM3->ARR = 0;
        power = 0;
        return;   			// Stop function
    }
    power = (u > 65535) ? 65535 : u;	    // Is u max?

    freq = 1000 + (power * (250000 - 1000)) / 65535;	    // Map u (0 → 65532) to frequency (1k → 250k)
    if (freq < 1000)     freq = 1000;				// Check if frequency is to big or small
    if (freq > 250000)   freq = 250000;				// or big

    TIM3_setFrequency(freq);  // Set PSC + ARR

    uint32_t arr = TIM3->ARR;	    // 50 % duty
    TIM3->CCR1 = (arr + 1) / 2;
}

void TIM3_setFrequency(uint32_t freq_hz){
    uint32_t psc = (timer_clk + (freq_hz * 65535) - 1) / (freq_hz * 65535);	    // PSC calculation
    if (psc > 0) psc -= 1;     // Formula give PSC+1, so take away 1

    period = (timer_clk / ((psc + 1) * freq_hz)) - 1;	// Calculating period (ARR)

    // Updating timer
    TIM3->PSC = psc;	//1;
    TIM3->ARR = period;	//35999;
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






