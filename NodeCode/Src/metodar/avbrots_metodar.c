//
// Fil: avbrots_metodar.c
// m.t.170913
//---------------------------------------

//---------------------------------------
// Inklusjonar og definisjonar
//---------------------------------------

#include <cmsis_boot/stm32f30x.h>
#include <cmsis_lib/stm32f30x_adc.h>
#include <cmsis_lib/stm32f30x_gpio.h>
#include <cmsis_lib/stm32f30x_usart.h>
#include <cmsis_lib/stm32f30x_dma.h>
#include <extern_dekl_globale_variablar.h>

//---------------------------------------
// Funksjonsprototypar
//---------------------------------------

void interrupt_init(void);
void SysTick_init(uint32_t hz);
void SysTick_Handler(void);
void USART3_IRQinit(void);
void USART3_EXTI28_IRQHandler(void);
void DMA1_CH2_IRQHandler(void);
void DMA1_CH3_IRQHandler(void);
void GPIO_sjekk_brytar(void);
int8_t USART_les(USART_TypeDef*);
void PWM_sett_vidde_TIM4_k4(uint16_t vidde);
void GPIO_brytaravprelling(void);
//---------------------------------------
// Funksjonsdeklarasjonar
//---------------------------------------
# define CORE_HZ	72000000U

// Oppsett av avbrotssystemet
//-------------------------------------
void interrupt_init(void) {
	// Alle avbrot med prioritetsverdi 2 el. høgare blir maskert
	// vekk (dei 4 MSb gir pri-verdien).
	// SysTick har fått avbrotsprioritet lik 1, sjå SysTick-fila.
	__set_BASEPRI(0x20);
}


/** \brief  SysTick initialization

    This function sets the period of SysTick based on the input
    variable Hz. Hz should not be too low as this would give an
    inaccurate tick length.

    Note: This function can be run mid program to change the tick
    length.

    \param [in]  hz  Desired frequency
 */
void SysTick_init(uint32_t hz){
	uint32_t reload = (CORE_HZ / hz) - 1;   // calculate reload
	if (reload > 0xFFFFFF) reload = 0xFFFFFF; // max 24‑bit value

	// Setup of SysTick
	NVIC_SetPriority(SysTick_IRQn, 1); // 0-31, 0 is highest
	SysTick->CTRL = 0;  // stop counting & interrupt
	SysTick->LOAD = reload; // new period
	SysTick->VAL = 0;  // clear current count
	SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk
					| SysTick_CTRL_TICKINT_Msk
					| SysTick_CTRL_ENABLE_Msk);
}

void USART3_IRQinit(void) {
	// Enable USART3 RX interrupt
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	// Configure NVIC for USART3
	NVIC_SetPriority(USART3_IRQn, 1);
	NVIC_EnableIRQ(USART3_IRQn);
}

void USART3_EXTI28_IRQHandler(void) {

	if (USART_GetITStatus(USART3,USART_IT_RXNE) != RESET) {
		// Store incoming byte
		USART3_rx[USART3_rx_irq] = USART_ReceiveData(USART3);
		USART3_rx_irq++;
	}
}

void DMA1_CH2_IRQHandler(void){
	if (DMA_GetITStatus(DMA1_IT_TE2) != RESET){
		GPIOE->BSRR = (1 << 10);
	}
}

void DMA1_CH3_IRQHandler(void){
	if (DMA_GetITStatus(DMA1_IT_TC3) != RESET){
		for (int i = 0; i < 9; ++i){
			data[i] = transmit_buffer[i];
		}
		GPIOE->BSRR = (1 << 10);
	}

}

// Avbrotsmetode ("Interrupt Service Routine", ISR)
// for avbrot fraa SysTick-taimeren
//----------------------------------------------------------------
void SysTick_Handler(void) {
	uint8_t kommando = 0;

	if (node == 0){

	}
	else if (node == 1){
		new_sample = 1;
	}

	tikkteljar_avprelling++;
	if(tikkteljar_avprelling >= 10) { //Har det gått 10 x 1 millisek sidan siste
		                              // brytaravlesing, så les brytarnivå og sjekk om
		GPIO_sjekk_brytar();          // det er eit nytt gyldig trykk.
		tikkteljar_avprelling = 0;
	}

	tikkteljar_sampling++;
	if(tikkteljar_sampling >= 10) { //Har det gått 10 millisek sidan sist, skal det utførast ny måling.

		ny_maaling = 1;
		tikkteljar_sampling = 0;
		  //Når brukaren gir "køyr"-signal frå PC-sida, skal målingane sendast
												 //med tidsreferanse til UART/USB-grensesnittet.

		tikkteljar_uartkomm++;
		if(tikkteljar_uartkomm >= 10) { //Kvar tiande måling skal
					                    // sendast med tidsreferanse til UART/USB, så gi melding til
			send_maaling = 1;          //hovudprogrammet om å køyra ny sending.
			tikkteljar_uartkomm = 0;
		}

	}

	tikkteljar_diodar++;
	if(tikkteljar_diodar >= 200) { //Har det gått 200 x 1 millisek sidan siste
			                              // oppdatering av diodebitane), så gi melding til
		oppdater_diodar = 1;          //tilstandsmaskinsmetoden.
		tikkteljar_diodar = 0;
	}

	GPIOC->ODR = GPIOC->ODR ^ GPIO_Pin_6; // Blinkesignal ut paa testpinne (PC6).


  //Sjekk om det er ny kommando fr� tastatur
	kommando = USART_les(USART2);
	if( kommando == 'k')  {  //Køyr i gong sending av målingane til loggaren
		send_maalingar_til_loggar = 1;
		legg_til_meldingshovud = 1; //Aller først skal hovudprogrammet leggja til STX

	}
	if( kommando == 's')  {  //Stopp sending av målingane til loggaren
		send_maalingar_til_loggar = 0;
		legg_til_meldingshale = 1;

	}
}
