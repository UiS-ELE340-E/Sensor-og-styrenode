//
// File: TIM_metodar.c
// m.t.311013
//---------------------------------------

//---------------------------------------
// Inclusions and definitions
//---------------------------------------
#include <metodar/TIM_metodar.h>

//---------------------------------------
// Function definitions
//---------------------------------------
void TIM2_init(void){
// TIM2 CH2 er satt opp som en PWM utgang på pinne PA1.

 //Deklarasjon av initialiseringsstrukturane.
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   TIM_OCInitTypeDef        TIM_OCInitStructure;

// Oppsett av TIM2 CH2 som PWM-utgang

 //Slepp f�rst til klokka paa TIM2.
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

   /* Time base configuration */
   TIM_TimeBaseStructure.TIM_Period = PWM_periode; //
   TIM_TimeBaseStructure.TIM_Prescaler = PWM_preskalering; // 0
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

   /* PWM1 Mode configuration: Channel2 */
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
   TIM_OCInitStructure.TIM_Pulse = PWM_vidde;
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

   TIM_OC2Init(TIM2, &TIM_OCInitStructure);

//   TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

//Så oppsett av GPIO-pinnen PA1 som blir brukt av TIM2-modulen
//------------------------------------------
//Deklarasjon av initialiseringsstrukturen.
	GPIO_InitTypeDef GPIO_InitStructure_TIM2;

  //Slepp til klokka paa GPIO-portA.
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // | RCC_AHBPeriph_AFIO

  //Konfigurer PA1.
	GPIO_InitStructure_TIM2.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure_TIM2.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure_TIM2.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_InitStructure_TIM2.GPIO_PuPd  = GPIO_PuPd_NOPULL;

  //Initialiser, dvs. last ned konfigurasjonen i modulen
	GPIO_Init(GPIOA, &GPIO_InitStructure_TIM2);

  //Knytt TIM2-pinnane til AF */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_1);

// Aktiver til slutt TIM2

    TIM_Cmd(TIM2, ENABLE);
}

//
void PWM_sett_vidde_TIM2_CH2(uint32_t vidde){

    TIM_OCInitTypeDef        TIM_OCInitStructure;

    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = vidde;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC2Init(TIM2, &TIM_OCInitStructure);

    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
}

/*
 * Setup of TIM4 with a 4 kHz 50% duty CLK signal to SCF filter
 * Using CH1 and PD12
 */
void TIM4_init(void){
    // --- Enable peripheral clocks ---
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE); // | RCC_AHBPeriph_AFIO

    // --- Configure TIM4 settings ---
    TIM_TimeBaseInitTypeDef TIM4Setup;
    TIM4Setup.TIM_Prescaler = 71;         // Gives 1 MHz = 1 us
    TIM4Setup.TIM_CounterMode = TIM_CounterMode_Up;
    TIM4Setup.TIM_Period = 249;           // Count up to 250 us
    TIM4Setup.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(TIM4,&TIM4Setup);

    // --- Configure TIM4 Output Compare ---
    TIM_OCInitTypeDef TIM4OCSetup;
    TIM4OCSetup.TIM_OCMode = TIM_OCMode_PWM1;
    TIM4OCSetup.TIM_OutputState = TIM_OutputState_Enable;
    TIM4OCSetup.TIM_Pulse = 125;          // Duty = 125 us
    TIM4OCSetup.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM4,&TIM4OCSetup);

    // --- Configure TIM4 to PD12 ---
    GPIO_InitTypeDef GPIO_InitStructure_TIM4;
    GPIO_InitStructure_TIM4.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure_TIM4.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure_TIM4.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure_TIM4.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure_TIM4);
    // Alternate function for TIM4
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_2); //.

    // Activate timer
    TIM_Cmd(TIM4,ENABLE);
}

void TIM4_deactivate(void){
    TIM_Cmd(TIM4,DISABLE);
}
