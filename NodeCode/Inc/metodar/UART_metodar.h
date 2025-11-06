/*
 * UART_metodar.h
 *
 *  Created on: Nov 2, 2025
 *      Author: STB_UiS
 */

#ifndef METODAR_UART_METODAR_H_
#define METODAR_UART_METODAR_H_

//---------------------------------------
// Inclusions and definitions
//---------------------------------------

#include <cmsis_boot/stm32f30x.h>
#include <cmsis_lib/stm32f30x_gpio.h>
#include <cmsis_lib/stm32f30x_rcc.h>
#include <cmsis_lib/stm32f30x_usart.h>
#include <cmsis_lib/stm32f30x_dma.h>
#include <extern_dekl_globale_variablar.h>

//---------------------------------------
// Function prototypes
//---------------------------------------
void USART1_init(void);
void USART1_DMA_init(uint8_t Tx);
void USART1_DMA_enable(uint8_t Tx);
void USART2_init(void);
void USART3_init(void);
void USART3_DMA_init(uint8_t Tx);
void USART3_DMA_enable(uint8_t Tx);

void USART_Put(USART_TypeDef*,uint8_t ch);
uint8_t USART_Get(USART_TypeDef*);
void USART_skriv(USART_TypeDef*, uint8_t ch);
uint8_t USART_les(USART_TypeDef*);
void USART_skriv_streng(USART_TypeDef*, uint8_t *streng);
void USART2_send_tid8_og_data16(uint8_t tid, int16_t loggeverdi);
void USART2_send_tid8_og_data16x3(uint8_t tid, int16_t loggeverdi1, int16_t loggeverdi2, int16_t loggeverdi3);
void USART2_handtering(uint8_t loggedata);
void USART2_handtering1(void);
void USART2_handtering2(uint16_t teljar);
void USART2andtering3(void);

#endif /* METODAR_UART_METODAR_H_ */
