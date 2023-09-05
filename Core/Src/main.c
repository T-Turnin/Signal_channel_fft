/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
/*	函 数 名: cfft
 *	功能说明: 对输入的复数组进行快速傅里叶变换（FFT）
 *	形    参: *_ptr 复数结构体组的首地址指针struct型
 *             FFT_N 表示点数
 *	返 回 值: 无
 *********************************************************************************************************
 */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint32_t i = 0;
	float thd_tmp = 0.0;
	float thd_all = 0;
	float THD2_50[51] = { 0 };
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_TIM8_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart1, (uint8_t*) g_u1_rx_buffer, 1); //打开串口2中断接收
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) &ADC1_Value_DMA, DMA_ADC_LENGTH);
	arm_cfft_radix4_instance_f32 scfft;
	arm_cfft_radix4_init_f32(&scfft, FFT_NUM_LENGTH, 0, 1); /* 初始化scfft结构体，设定FFT相关参数 */
	HAL_TIM_Base_Start_IT(&htim8); //定时器2触发adc采集
	HAL_Delay(20);
	HAL_TIM_Base_Stop_IT(&htim8); //定时器2触发adc采集
	for (i = 0; i < FFT_NUM_LENGTH; i++) {
		ADC1_FFT_RAW[i] = 3.3f * ADC1_Value_DMA[i] / 4096;
	}
	printf(
			"--------------------------------------------------------------\r\n");
	printf("采集到的数据：\r\n");
	for (i = 0; i < FFT_NUM_LENGTH; i++) {
		printf("ADC1_FFT_RAW[%ld] = % 0.5f\r\n", i, ADC1_FFT_RAW[i]);
	}

	for (i = 0; i < FFT_NUM_LENGTH; i++) {
		ADC1_FFT_Input[2 * i] = ADC1_FFT_RAW[i];
		ADC1_FFT_Input[2 * i + 1] = 0;
	}
	//		printf("加窗:\r\n");
	//		for (i = 0; i < FFT_NUM_LENGTH; i++) {
	//
	//			ADC1_FFT_RAW[2 * i] = ADC1_FFT_RAW[2 * i]
	//					* (0.5 - 0.5 * cos(2 * M_PI * i / (1024 - 1)));
	//		}
	//		printf(
	//				"--------------------------------------------------------------\r\n");
	//		printf("加窗后电压:\r\n");
	//		for (i = 0; i < FFT_NUM_LENGTH; i++) {
	//			printf("ADC1_FFT_RAW[%ld] = % 0.5f\r\n", 2 * i,
	//					ADC1_FFT_RAW[2 * i]);
	//		}
	//		for (i = 0; i < FFT_NUM_LENGTH; i++) {
	//			printf("% 0.5f\r\n", ADC1_FFT_RAW[2 * i]);
	//		}
	arm_cfft_radix4_f32(&scfft, ADC1_FFT_Input); /* FFT计算（基4） */

	arm_cmplx_mag_f32(ADC1_FFT_Input, ADC1_FFT_Output, FFT_NUM_LENGTH); /* 把运算结果复数求模得幅值 */

	printf(
			"--------------------------------------------------------------\r\n");

	printf("FFT计算结果:\r\n");
	for (i = 0; i < FFT_NUM_LENGTH; i++) {
		printf("%ld点: % 0.5f + %0.5f i \r\n", i, ADC1_FFT_Input[2 * i],
				ADC1_FFT_Input[2 * i + 1]);
	}
	printf(
			"--------------------------------------------------------------\r\n");
	printf("频域幅度:\r\n");
	for (i = 0; i < FFT_NUM_LENGTH; i++) {
		printf("%ld点: %0.5f\r\n", i, ADC1_FFT_Output[i]);
	}
	printf(
			"--------------------------------------------------------------\r\n");
	printf("谐波:\r\n");
	for (i = 2; i < FFT_NUM_LENGTH; i++) {
		printf("%ld次谐波: %0.5f%%\r\n", i, ADC1_FFT_Output[i] / ADC1_FFT_Output[1] * 100);
	}
	for (i = 0; i < FFT_NUM_LENGTH; i++) {
			u3_printf("%0.5f\r\n", i, ADC1_FFT_RAW[i]);
		}
	HAL_Delay(10000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//			printf(
//					"--------------------------------------------------------------\r\n");
//
//			printf("n次谐波对应幅值:\r\n");
//			for (i = 2; i < 51; i++) {
//				thd_tmp += ADC1_FFT_Output[4 * i] * ADC1_FFT_Output[4 * i];
//				printf("%ld次幅值: %0.5f\r\n", i, ADC1_FFT_Output[4 * i]);
//
//			}
//			printf(
//					"--------------------------------------------------------------\r\n");
//
//			printf("畸变率:\r\n");
//
//			thd_all = sqrt(thd_tmp) / ADC1_FFT_Output[4] * 100;
//			printf("总畸变率: %0.5f %%\r\n", thd_all);
//			for (i = 2; i < 51; i++) {
//				printf("%ld 次谐波:%0.3f %%\r\n", i,
//						ADC1_FFT_Output[4 * i] / ADC1_FFT_Output[4] * 100);
//			}
//			thd_tmp = 0;
//			sum_FFT_flag = 0;
//			memset(ADC1_FFT_RAW, 0, sizeof(ADC1_FFT_RAW));
//			memset(ADC1_FFT_Output, 0, sizeof(ADC1_FFT_Output));
//			HAL_TIM_Base_Start_IT(&htim8); //定时器2触发adc采集
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
