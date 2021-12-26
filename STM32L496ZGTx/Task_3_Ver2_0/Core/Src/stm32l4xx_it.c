/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include <string.h>
#include "stm32l4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 6
#define SEG_DP 9
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int hourFirst = 1, hourSecond = 5;
int minuteFirst = 3, minuteSecond = 0;
int secondFirst = 0, secondSecond = 0;
int showHHMM = 1, showMMSS = 0;
int buttonMs = 0;
int buttonDelay = 500;
const uint16_t  tableOfSegments[] =  {
		1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 1 << SEG_D | 1 << SEG_E | 1 << SEG_F, 			  // DIGIT 0
		1 << SEG_B | 1 << SEG_C, 													 			  // DIGIT 1
		1 << SEG_A | 1 << SEG_B | 1 << SEG_E | 1 << SEG_D | 1 << SEG_G, 			 			  // DIGIT 2
		1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 1 << SEG_D | 1 << SEG_G, 			 			  // DIGIT 3
		1 << SEG_B | 1 << SEG_C | 1 << SEG_G | 1 << SEG_F, 							 			  // DIGIT 4
		1 << SEG_A | 1 << SEG_F | 1 << SEG_G | 1 << SEG_C | 1 << SEG_D,				 			  // DIGIT 5
		1 << SEG_A | 1 << SEG_F | 1 << SEG_G | 1 << SEG_C | 1 << SEG_D | 1 << SEG_E, 			  // DIGIT 6
		1 << SEG_A | 1 << SEG_B | 1 << SEG_C,										 			  // DIGIT 7
		1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 1 << SEG_D | 1 << SEG_E | 1 << SEG_F | 1 << SEG_G, // DIGIT 8
		1 << SEG_A | 1 << SEG_B | 1 << SEG_C | 1 << SEG_D | 1 << SEG_F | 1 << SEG_G, 			  // DIGIT 9

};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void changeSeconds();
void changeMinutes();
void changeHours();

void inputHandling();
void showDigit(const char * digitName);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void changeSeconds()
{
	if(secondSecond < 9)
		secondSecond++;
	else if(secondSecond == 9)
	{
		if(secondFirst < 5)
		{
			secondSecond = 0;
			secondFirst++;
		}
		else // secondSecond == 9 && secondFirst == 5
		{
			secondSecond = 0;
			secondFirst = 0;
			changeMinutes();
		}
	}
}

void changeMinutes()
{
	if(minuteSecond < 9)
		minuteSecond++;
	else if(minuteSecond == 9)
	{
		if(minuteFirst < 5)
		{
			minuteSecond = 0;
			minuteFirst++;
		}
		else // minutesSecond == 9 && minutesFirst == 5
		{
			minuteSecond = 0;
			minuteFirst = 0;
			changeHours();
		}
	}
}

void changeHours()
{
	if(hourFirst <= 1 && hourSecond < 9)
		hourSecond++;
	else if(hourFirst <= 1 && hourSecond == 9)
	{
		hourSecond = 0;
		hourFirst++;
	}
	else if(hourFirst == 2 && hourSecond < 3)
		hourSecond++;
	else
	{
		hourSecond = 0;
		hourFirst = 0;
	}
}
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */
  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */
  /*
  static int miliSeconds = 0;
  miliSeconds++;
  inputHandling();
  if((miliSeconds % 1000) == 0 || miliSeconds == 1)
  {
	   HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
	   if(showHHMM)
	   {
		   if(miliSeconds / 1000 == 0)
		   {
			   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[hourFirst], GPIO_PIN_SET);
		   }
		   else if(miliSeconds / 1000 == 1)
		   {
			   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[hourSecond], GPIO_PIN_SET);
		   }
		   else if(miliSeconds / 1000 == 2)
		   {
			   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[minuteFirst], GPIO_PIN_SET);
		   }
		   else if(miliSeconds / 1000 == 3)
		   {
			   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[minuteSecond], GPIO_PIN_SET);

			   return;
		   }
		   else if(miliSeconds / 1000 == 4)
		   {
			   miliSeconds = 0;
		   }
		   changeSeconds();
	   }
	   else if(showMMSS)
	   {
		   if(miliSeconds / 1000 == 0)
		   {
			   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[minuteFirst], GPIO_PIN_SET);
		   }
		   else if(miliSeconds / 1000 == 1)
		   {
			   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[minuteSecond], GPIO_PIN_SET);
		   }
		   else if(miliSeconds / 1000 == 2)
		   {
			   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[secondFirst], GPIO_PIN_SET);
		   }
		   else if(miliSeconds / 1000 == 3)
		   {
			   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[secondSecond], GPIO_PIN_SET);
			   return;
		   }
		   else if(miliSeconds / 1000 == 4)
		   {
			   miliSeconds = 0;
		   }
		   changeSeconds();

	   }
  }
  */
  static int miliSeconds = 0;
  inputHandling();
  int digitOf4Sec = miliSeconds % 4;
  if((digitOf4Sec / 4) == 0)
  {
	  switch(digitOf4Sec)
	  {
		  case 0:
			   showDigit("first");
			  break;
		  case 1: // digit 2
			   showDigit("second");
			  break;
		  case 2: // digit 3
			   showDigit("third");
			  break;
		  case 3: // digit 4
			  showDigit("fourth");
			  break;

	  }
  }
  if(miliSeconds != 0)
  {
	  if(miliSeconds / 1000 == 4)
	  {
		  miliSeconds = 0;
	  }
	  if(miliSeconds % 1000 == 0)
	  {
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_9, GPIO_PIN_SET);
		  changeSeconds();
	  }

  }
  miliSeconds++;
  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */
void inputHandling()
{
	buttonMs++;
	if(buttonMs < buttonDelay)
		return;
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2 ) == GPIO_PIN_RESET)
	{
		buttonMs = 0;
		showMMSS = 1;
		showHHMM = 0;
		return;
	}
	else if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_RESET)
	{
		buttonMs = 0;
		showMMSS = 0;
		showHHMM = 1;
		return;
	}

}

void showDigit(const char * digitName)
{
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
	if(strcmp(digitName, "first") == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
		if(showHHMM)
		{
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[hourFirst] | GPIO_PIN_9, GPIO_PIN_SET);
		}
		else if(showMMSS)
		{
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[minuteFirst] | GPIO_PIN_9, GPIO_PIN_SET);
		}

	}
	else if(strcmp(digitName, "second") == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
		if(showHHMM)
		{
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[hourSecond] | GPIO_PIN_9, GPIO_PIN_SET);
		}
		else if(showMMSS)
		{
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[minuteSecond] | GPIO_PIN_9, GPIO_PIN_SET);
		}
	}
	else if(strcmp(digitName, "third") == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		if(showHHMM)
		{
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[minuteFirst] | GPIO_PIN_9, GPIO_PIN_SET);
		}
		else if(showMMSS)
		{
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[secondFirst] | GPIO_PIN_9, GPIO_PIN_SET);
		}
	}
	else if(strcmp(digitName, "fourth") == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		if(showHHMM)
		{
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[minuteSecond], GPIO_PIN_SET);
		}
		else if(showMMSS)
		{
			   HAL_GPIO_WritePin(GPIOG, tableOfSegments[secondSecond], GPIO_PIN_SET);
		}
	}
}
/* USER CODE END 1 */
