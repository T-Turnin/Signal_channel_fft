/*
 * bsp_tim.h
 *
 *  Created on: Jun 29, 2023
 *      Author: 黎
 */

#ifndef BSP_TIM_H_
#define BSP_TIM_H_

#define DMA_ADC_LENGTH 256
#define FFT_CHANNEL_ADC_LENGTH 2048
#define FFT_NUM_LENGTH 256
/*
 * DMA
 */
extern uint32_t ADC1_Value_DMA[DMA_ADC_LENGTH];

/*
 * 	不同通道的电压
 */
extern float ADC1_FFT_RAW[FFT_NUM_LENGTH];
extern float ADC1_FFT_Input[FFT_CHANNEL_ADC_LENGTH];
extern float ADC1_FFT_Output[FFT_NUM_LENGTH];


extern uint16_t g_adc_index;
extern uint16_t g_dma_index;

extern uint8_t sum_FFT_flag ;

#endif /* BSP_TIM_H_ */
