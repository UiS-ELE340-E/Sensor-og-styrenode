//---------------------------------------
// Inclusions and definitions
//---------------------------------------

#include <cmsis_boot/stm32f30x.h>
#include <cmsis_lib/stm32f30x_adc.h>
#include <cmsis_lib/stm32f30x_rcc.h>
#include <cmsis_lib/stm32f30x_gpio.h>

//---------------------------------------
// Function prototypes
//---------------------------------------
void ADC3_init(void);

//---------------------------------------
// Function definitions
//---------------------------------------
void ADC3_init(void){
    /* Clock & GPIO */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC34, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    GPIO_InitTypeDef gpio = {0};
    gpio.GPIO_Pin  = GPIO_Pin_1;
    gpio.GPIO_Mode = GPIO_Mode_AN;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &gpio);

    /* ADC common */
    ADC_CommonInitTypeDef com = {0};
    com.ADC_Mode = ADC_Mode_Independent;
    com.ADC_Clock = ADC_Clock_SynClkModeDiv4;   // 72 MHz / 4 = 18 MHz < 30 MHz
    ADC_CommonInit(ADC3, &com);

    /* ADC instance */
    ADC_InitTypeDef adc = {0};
    adc.ADC_Resolution = ADC_Resolution_12b;
    adc.ADC_ContinuousConvMode = DISABLE;
    adc.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
    adc.ADC_DataAlign = ADC_DataAlign_Right;
    adc.ADC_NbrOfRegChannel = 1;
    ADC_Init(ADC3, &adc);

    ADC_RegularChannelConfig(ADC3, ADC_Channel_1, 1, ADC_SampleTime_19Cycles5);

    /* Calibration & enable */
    ADC_VoltageRegulatorCmd(ADC3, ENABLE);
    // Wait for regulator to power on
    for (volatile int i = 0; i < 1000; ++i) __NOP();   // ~10 µs wait time
    ADC_StartCalibration(ADC3);
    while (ADC_GetCalibrationStatus(ADC3)) {}
    ADC_Cmd(ADC3, ENABLE);

    while (ADC_GetFlagStatus(ADC3, ADC_FLAG_RDY) == RESET);
}
