//
// Fil: UART_metodar.c
// m.t.170913
//---------------------------------------

//---------------------------------------
// Inclusions and definitions
//---------------------------------------
#include <metodar/UART_metodar.h>

//---------------------------------------
// Function definitions
//---------------------------------------
void USART1_init(void)
{
    // --- Enable peripheral clocks ---
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);   // USART1 clock
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);      // GPIOA clock

    // --- Configure USART1 clock settings ---
    USART_ClockInitTypeDef USART1_ClockInitStructure;
    USART_ClockStructInit(&USART1_ClockInitStructure);
    USART_ClockInit(USART1, &USART1_ClockInitStructure);

    // --- Configure USART1 parameters ---
    USART_InitTypeDef USART1_InitStructure;
    USART1_InitStructure.USART_BaudRate = 115200;
    USART1_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART1_InitStructure.USART_StopBits = USART_StopBits_1;
    USART1_InitStructure.USART_Parity = USART_Parity_No;
    USART1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART1_InitStructure);

    // --- Configure USART1 TX (PA9) ---
    GPIO_InitTypeDef GPIO_InitStructure_UART1;
    GPIO_InitStructure_UART1.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure_UART1.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_UART1.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure_UART1.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure_UART1.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure_UART1);
    // Alternate function for USART1 TX
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);

    // --- Configure USART1 RX (PA10) ---
    GPIO_InitStructure_UART1.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure_UART1.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_UART1.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure_UART1.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure_UART1);
    // Alternate function for USART1 RX
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
}

void USART1_DMA_init(uint8_t Tx){
    // --- Configure DMA ---
    DMA_InitTypeDef DMA_InitStructure;
    if (Tx == 1){
    	DMA_DeInit(DMA1_Channel4);
    }
    else{
    	DMA_DeInit(DMA1_Channel5);
    }
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->RDR;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)transmit_buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = buffer_size;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    if (Tx == 1){
    	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
    }
    else{
    	DMA_Init(DMA1_Channel5, &DMA_InitStructure);
    }
}

void USART1_DMA_enable(uint8_t Tx){
	if (Tx == 1){
		// --- Enable DMA for USART3 TX ---
		USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	}
	else{
		// --- Enable DMA for USART3 RX ---
		USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
	}

    // --- Enable USART3 ---
    USART_Cmd(USART1, ENABLE);

	if (Tx == 1){
		// --- Enable DMA ---
		DMA_Cmd(DMA2_Channel4, ENABLE);
	}
	else{
	    // --- Enable DMA ---
	    DMA_Cmd(DMA2_Channel5, ENABLE);
	}
}

// Initialization for for USART2
// USART 2 is used for communication to PC via UART/USB FTDI-circuit on shield card
//----------------------------------------------------------------------------
void USART2_init(void)
{
    // --- Enable peripheral clocks ---
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);   // USART2 clock
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);      // GPIOA clock

    // --- Configure USART2 clock settings ---
    USART_ClockInitTypeDef USART2_ClockInitStructure;
    USART_ClockStructInit(&USART2_ClockInitStructure);
    USART_ClockInit(USART2, &USART2_ClockInitStructure);

    // --- Configure USART2 parameters ---
    USART_InitTypeDef USART2_InitStructure;
    USART2_InitStructure.USART_BaudRate = 115200;
    USART2_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART2_InitStructure.USART_StopBits = USART_StopBits_1;
    USART2_InitStructure.USART_Parity = USART_Parity_No;
    USART2_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART2_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2, &USART2_InitStructure);

    // --- Configure USART2 TX (PA2) ---
    GPIO_InitTypeDef GPIO_InitStructure_UART2;
    GPIO_InitStructure_UART2.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure_UART2.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_UART2.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure_UART2.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure_UART2.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure_UART2);
    // Alternate function for USART2 TX
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);

    // --- Configure USART2 RX (PA3) ---
    GPIO_InitStructure_UART2.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure_UART2.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_UART2.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure_UART2);
    // Alternate function for USART2 RX
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);

    // --- Enable USART2 ---
    USART_Cmd(USART2, ENABLE);

    // --- Send welcome message ---
    USART_skriv_streng(USART2, (uint8_t *)"--\nSTM32F3 er klar!\n\r");
}

void USART3_init(void)
{
    // --- Enable peripheral clocks ---
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);

    // --- Configure USART3 clock settings ---
    USART_ClockInitTypeDef USART3_ClockInitStructure;
    USART_ClockStructInit(&USART3_ClockInitStructure);
    USART_ClockInit(USART3, &USART3_ClockInitStructure);

    // --- Configure USART3 parameters ---
    USART_InitTypeDef USART3_InitStructure;
    USART3_InitStructure.USART_BaudRate = 115200;
    USART3_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART3_InitStructure.USART_StopBits = USART_StopBits_1;
    USART3_InitStructure.USART_Parity = USART_Parity_No;
    USART3_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART3_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART3, &USART3_InitStructure);

    // --- Configure USART3 TX (PD8) ---
    GPIO_InitTypeDef GPIO_InitStructure_UART3;
    GPIO_InitStructure_UART3.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure_UART3.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_UART3.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure_UART3.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure_UART3.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure_UART3);
    // Alternate function for USART3 TX
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_7);

    // --- Configure USART3 RX (PD9) ---
    GPIO_InitStructure_UART3.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure_UART3.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_UART3.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure_UART3.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure_UART3);
    // Alternate function for USART3 RX
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_7);
}

void USART3_DMA_init(uint8_t Tx){
	// --- Enable peripheral clocks ---
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// --- Deinitialize DMA1 channel 2 and 3 ---
	DMA_DeInit(DMA1_Channel2);
    DMA_DeInit(DMA1_Channel3);
    // --- Configure DMA ---
    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)transmit_buffer;
    DMA_InitStructure.DMA_BufferSize = buffer_size;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    if (Tx == 1){
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->TDR;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
        DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    	DMA_Init(DMA1_Channel2, &DMA_InitStructure);
        // Enable the TX-complete / error interrupts
        DMA_ITConfig(DMA1_Channel2, DMA_ISR_TCIF1 | DMA_ISR_TEIF1, ENABLE);
        NVIC_SetPriority(DMA1_Channel2_IRQn, 1);
		NVIC_EnableIRQ(DMA1_Channel2_IRQn);
    }
    else{
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->RDR;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
        DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    	DMA_Init(DMA1_Channel3, &DMA_InitStructure);
        // Enable the RX-complete / error interrupts
        DMA_ITConfig(DMA1_Channel3, DMA_ISR_TCIF1 | DMA_ISR_TEIF1, ENABLE);
        NVIC_SetPriority(DMA1_Channel3_IRQn, 1);
        NVIC_EnableIRQ(DMA1_Channel3_IRQn);
    }
}

void USART3_DMA_enable(uint8_t Tx){
	if (Tx == 1){
		// --- Enable DMA for USART3 TX ---
		USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
	}
	else{
		// --- Enable DMA for USART3 RX ---
		USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
	}

    // --- Enable USART3 ---
    USART_Cmd(USART3, ENABLE);

	if (Tx == 0){
	    // --- Enable DMA RX ---
	    DMA_Cmd(DMA1_Channel3, ENABLE);
	}
}

void USART_Put(USART_TypeDef* USARTx, uint8_t ch)
{
    USART_SendData(USARTx, (uint8_t) ch);
    //Loop until the end of transmission
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
        {
        ;
        }

}

uint8_t USART_Get(USART_TypeDef* USARTx)
{
    while ( USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
        {
        ;
        }
    return (uint8_t)USART_ReceiveData(USARTx);
}


uint8_t USART_les(USART_TypeDef* USARTx)
{
   if ( USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) != RESET)
        {
	   return (uint8_t)USART_ReceiveData(USARTx);
   }
   else {
       return (uint8_t)0x00;
   }
}

void USART_skriv(USART_TypeDef* USARTx, uint8_t data)
{
    USART_SendData(USARTx, (uint8_t) data);
    //Loop until the end of transmission
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
        {
        ;
        }

}
void USART_skriv_streng(USART_TypeDef* USARTx,uint8_t *streng)
{
    while( *streng != 0) {   // Skriv ut ein 0-terminert tekststreng
    	USART_skriv(USART2, *streng);
    	streng++;
    }
}

void USART2_send_tid8_og_data16(uint8_t tid, int16_t loggeverdi)  {
	uint8_t tid0, tid1;
    int16_t data0, data1, data2, data3;

    tid0 = tid;
    tid1 = tid0 >> 4;

	USART_skriv(USART2,'T');
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(tid1 & 0x0F)]));   // Send MS Hex-siffer av ein tidsbyten
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(tid0 & 0x0F)])); // Send LS Hex-siffer av ein tidsbyten

	data0 = loggeverdi; //
	data1 = data0 >> 4; // Under skifting er det viktig at forteiknet blir med, difor int.
	data2 = data1 >> 4;
	data3 = data2 >> 4;

	USART_skriv(USART2,'L');            // L for loggedata
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data3 & 0x000F)])); // Send MS Hex-siffer av 16-bitsdata
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data2 & 0x000F)]));
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data1 & 0x000F)]));
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data0 & 0x000F)])); // Send LS Hex-siffer av dei 16 bitane
}

void USART2_send_tid8_og_data16x3(uint8_t tid, int16_t loggeverdi1, int16_t loggeverdi2, int16_t loggeverdi3)  {
	uint8_t tid0, tid1;
    int16_t data0, data1, data2, data3;

    tid0 = tid;
    tid1 = tid0 >> 4;

	USART_skriv(USART2,'T');
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(tid1 & 0x0F)]));   // Send MS Hex-siffer av ein tidsbyten
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(tid0 & 0x0F)])); // Send LS Hex-siffer av ein tidsbyten

	data0 = loggeverdi1; //
	data1 = data0 >> 4; // Under skifting er det viktig at forteiknet blir med, difor int.
	data2 = data1 >> 4;
	data3 = data2 >> 4;

	USART_skriv(USART2,'X');            // L for loggedata
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data3 & 0x000F)])); // Send MS Hex-siffer av 16-bitsdata
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data2 & 0x000F)]));
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data1 & 0x000F)]));
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data0 & 0x000F)])); // Send LS Hex-siffer av dei 16 bitane

	data0 = loggeverdi2; //
	data1 = data0 >> 4; // Under skifting er det viktig at forteiknet blir med, difor int.
	data2 = data1 >> 4;
	data3 = data2 >> 4;

	USART_skriv(USART2,'Y');            // L for loggedata
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data3 & 0x000F)])); // Send MS Hex-siffer av 16-bitsdata
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data2 & 0x000F)]));
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data1 & 0x000F)]));
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data0 & 0x000F)])); // Send LS Hex-siffer av dei 16 bitane

	data0 = loggeverdi3; //
	data1 = data0 >> 4; // Under skifting er det viktig at forteiknet blir med, difor int.
	data2 = data1 >> 4;
	data3 = data2 >> 4;

	USART_skriv(USART2,'Z');            // L for loggedata
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data3 & 0x000F)])); // Send MS Hex-siffer av 16-bitsdata
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data2 & 0x000F)]));
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data1 & 0x000F)]));
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[(data0 & 0x000F)])); // Send LS Hex-siffer av dei 16 bitane
}
void USART2_handtering(uint8_t loggedata)  {
    uint8_t data;
	USART_skriv(USART2,'D');
	USART_skriv(USART2,':');
    data = loggedata >> 4;
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[data]));   // Send MSB av maalinga
    data = loggedata & 0x0F;
	USART_skriv(USART2,(uint8_t)(hex2ascii_tabell[data])); // Send LSB
	USART_skriv(USART2,' ');
}
void USART2_handtering1(void)  {
    testmaaling += 10;
    if(testmaaling >= 500) {
    	testmaaling = 0;
    }

    maaling_teljar++;
    if(maaling_teljar > 2000) {

    	maaling_teljar = 1;
//    	send_ny_tidsserie_1000 = 0;

    }

    USART_skriv(USART1, (uint8_t)(maaling_teljar >> 8));   // Send MSB av maalinga
	USART_skriv(USART1, (uint8_t)(maaling_teljar & 0xFF)); // Send LSB

	USART_skriv(USART1,(uint8_t)(testmaaling >> 8));   // Send MSB av maalinga
	USART_skriv(USART1,(uint8_t)(testmaaling & 0xFF)); // Send LSB


	testmaaling += 10;
	if(testmaaling >= 500) {
		testmaaling = 0;
	}

	maaling_teljar++;
	if(maaling_teljar > 2000) {

		maaling_teljar = 1;
	}
}

void USART2_handtering2(uint16_t teljar)  {


	uint8_t data, i = 98;

    data = teljar;   // sender LSB av teljaren f�rst
    USART_skriv(USART1,data);  // Skriving av data via UART/USB-modulen.

    data = (teljar>>8);   // sender s� MSB av teljaren
    USART_skriv(USART1,data);  // Skriving av data via UART/USB-modulen.

	data = 0;
	while(i>0)  // S� skriving av 98 nullar.
		{
		USART_skriv(USART1,data);
		i--;
	    }

}

void USART2_handtering3(void)  {

	uint8_t teikn = 0x30;
	uint8_t ny_kommando;
	uint8_t kommando ='2';


    //Send velkomst via UART/USB-modul
	USART_skriv_streng(USART1,(uint8_t *)"--\nVelkommen!\n\r");  // Ny linje og retur til linjestart etterp�.

	while(1)   // Endelaus l�kkje
		{
	    ny_kommando = USART_les(USART1);  // Sjekk om det er ny kommando fr� tastatur
		if(ny_kommando != 0)  {      // I s� fall, oppdater kommando, ellers kommando som f�r
			kommando = ny_kommando;
		}

		switch(kommando) {           // Tolk kommando
		case 'g': //GPIO_snu_PC9();
			break; // Gr�n blink
		case 'b': //GPIO_snu_PC8();
			break; // Bl� blink
		}

//		venting_vhja_nedteljing(1000000);  // Det m� g� litt tid mellom blinka

		USART_skriv(USART1,teikn++);    // Skriving av ASCII-koda teikn via UART/USB-modulen.
		USART_skriv(USART1,'\r');       // retur til same felt.
		if(teikn >'z')
		   {
		   teikn = 0x30;
		   }

    }
}
