/*
 * tim_func.c
 *
 *  Created on: Jun 12, 2023
 *      Author: 黎
 */
#include "main.h"

/*
 * DMA
 */
uint32_t ADC1_Value_DMA[DMA_ADC_LENGTH] = { 0 };

/*
 * 	不同通道的电压
 */
float ADC1_FFT_RAW[FFT_NUM_LENGTH] = { 0 };
float ADC1_FFT_Input[FFT_CHANNEL_ADC_LENGTH] = { 0 };
float ADC1_FFT_Output[FFT_NUM_LENGTH] = { 0 };

volatile uint16_t g_FFT_index = 0;

uint8_t sum_FFT_flag = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == (&htim8)) //TIM2的中断服务函数
		{



	}

}

