/*
 * bsp_adc.c
 *
 *  Created on: 2023年6月30日
 *      Author: 黎
 */

#include "main.h"



/* ADC采集完成后会进入该回调函数， 标记ADC转换完成并停止转换，
 *    	以免之前采集到的数据被覆盖
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (hadc->Instance == ADC1) {


	}
	if (hadc->Instance == ADC3) {


	}

	if (hadc->Instance == ADC2) {


	}
}

