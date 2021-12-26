/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

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
GPIO_InitTypeDef LED_C_init;
GPIO_InitTypeDef LED_D_init;
GPIO_InitTypeDef LED_E_init;

int values_for_LEDS_C[] = {
		GPIO_PIN_6, // LED 0
		GPIO_PIN_7, // LED 1
		GPIO_PIN_8, // LED 2
		GPIO_PIN_9  // LED 3
};

int values_for_LEDS_E[] = {
		GPIO_PIN_4, // LED 4
		GPIO_PIN_5, // LED 6
		GPIO_PIN_6  // LED 7
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void ledInit();
void lightLED(int numberOfLED);
void resetLED(int numberOfLED);
void lightAllLEDS();
void resetAllLEDS();
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  ledInit();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  lightAllLEDS();
	  resetAllLEDS();
	  HAL_Delay(2000);
    /* USER CODE BEGIN 3 */
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
void ledInit()
{
	LED_C_init.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
	LED_C_init.Alternate = 0;
	LED_C_init.Mode = GPIO_MODE_OUTPUT_PP;
	LED_C_init.Speed = GPIO_SPEED_FREQ_LOW;
	LED_C_init.Pull = GPIO_NOPULL;

	LED_D_init.Pin = GPIO_PIN_3;
	LED_D_init.Alternate = 0;
	LED_D_init.Mode = GPIO_MODE_OUTPUT_PP;
	LED_D_init.Speed = GPIO_SPEED_FREQ_LOW;
	LED_D_init.Pull = GPIO_NOPULL;

	LED_E_init.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	LED_E_init.Alternate = 0;
	LED_E_init.Mode = GPIO_MODE_OUTPUT_PP;
	LED_E_init.Speed = GPIO_SPEED_FREQ_LOW;
	LED_E_init.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOC, &LED_C_init);
	HAL_GPIO_Init(GPIOD, &LED_D_init);
	HAL_GPIO_Init(GPIOE, &LED_E_init);



}

void lightLED(int numberOfLED)
{
	if(numberOfLED >= 0 && numberOfLED <= 3)
		HAL_GPIO_WritePin(GPIOC, values_for_LEDS_C[numberOfLED], GPIO_PIN_SET);
	else if(numberOfLED == 4)
		HAL_GPIO_WritePin(GPIOE, values_for_LEDS_E[0], GPIO_PIN_SET);
	else if(numberOfLED == 5)
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(GPIOE, values_for_LEDS_E[numberOfLED-5], GPIO_PIN_SET);
}

void lightAllLEDS()
{
	int i;
	for(i = 0; i < 8; i++)
	{
		lightLED(i);
		HAL_Delay(200);
	}
}

void resetLED(int numberOfLED)
{
	if(numberOfLED >= 0 && numberOfLED <= 3)
		HAL_GPIO_WritePin(GPIOC, values_for_LEDS_C[numberOfLED], GPIO_PIN_RESET);
	else if(numberOfLED == 4)
		HAL_GPIO_WritePin(GPIOE, values_for_LEDS_E[0], GPIO_PIN_RESET);
	else if(numberOfLED == 5)
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(GPIOE, values_for_LEDS_E[numberOfLED-5], GPIO_PIN_RESET);

}

void resetAllLEDS()
{
	int i;
	for(i = 0; i < 8; i++)
	{
		resetLED(i);
		HAL_Delay(200);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

