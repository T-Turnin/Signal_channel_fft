/*
 * bsp_adc.c
 *
 *  Created on: 2023��6��30��
 *      Author: ��
 */

#include "main.h"



/* ADC�ɼ���ɺ�����ûص������� ���ADCת����ɲ�ֹͣת����
 *    	����֮ǰ�ɼ��������ݱ�����
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (hadc->Instance == ADC1) {


	}
	if (hadc->Instance == ADC3) {


	}

	if (hadc->Instance == ADC2) {


	}
}

