/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32l4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "kamami_l496_mems.h"
#include  <string.h>
#include <math.h>
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
int showX = 1;
int showY = 0;
int showZ = 0;

float x, y, z;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

void inputHandling();
void makeDigitFromFloatValue(int pos, float input, int * digitToSet);
void showDigit(const char * digitName);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
struct mems_xyz_res acc; // structure for accelerometr results
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
  static int miliSec = 0;
  inputHandling();
  int digitOf4Sec = miliSec % 4;
  switch(digitOf4Sec)
  {
	  case 0:
		  showDigit("axis");
		  break;
	  case 1: // digit 2
		  showDigit("first");
		  break;
	  case 2: // digit 3
		  showDigit("second");
		  break;
	  case 3: // digit 4
		  showDigit("third");
		  break;
  }
  if(miliSec != 0)
  {
	  if(miliSec / 1000 == 4)
		  miliSec = 0;
	  if(miliSec % 1000 == 0)
	  {
		  mems_acc_read_xyz(&acc);
		  x = floorf((acc.x * 2.0f / MEMS_ACC_MAXVAL) * 100) / 100; //acc.x * 2.0f / MEMS_ACC_MAXVAL;
		  y = floorf((acc.y * 2.0f / MEMS_ACC_MAXVAL) * 100) / 100; //acc.y * 2.0f / MEMS_ACC_MAXVAL;
		  z = floorf((acc.z * 2.0f / MEMS_ACC_MAXVAL) * 100) / 100; //acc.z * 2.0f / MEMS_ACC_MAXVAL;
	  }
  }
  miliSec++;

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
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0) == GPIO_PIN_RESET) // 	  JOY RIGHT, Y
	{
		showX = 0;
		showY = 1;
		showZ = 0;
	}
	else if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1) == GPIO_PIN_RESET) // JOY LEFT,  X
	{
		showX = 1;
		showY = 0;
		showZ = 0;
	}
	else if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2) == GPIO_PIN_RESET) // JOY DOWN,  Z
	{
		showX = 0;
		showY = 0;
		showZ = 1;
	}
	if(buttonMs == buttonDelay)
		buttonMs = 0;

}

void makeDigitFromFloatValue(int pos, float input, int * digitToSet)
{
	if(input < 0)
	{
		input *= -1;
	}

	int number = input * 100;
	/*if(input < 10)
	{
		if(pos == 1)
			*digitToSet = 0;
		else if(pos == 2)
			*digitToSet = 0;
		else
			*digitToSet = number % 10;
	}*/
	if(input < 100)
	{
		if(pos == 1)
			*digitToSet = 0;
		else if(pos == 2)
		{
			number /= 10;
			*digitToSet = number % 10;
		}
		else
			*digitToSet = number % 10;
	}

}

void showDigit(const char * digitName)
{
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_9, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
	if(strcmp(digitName, "axis") == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
		if(showX)
			HAL_GPIO_WritePin(GPIOG, tableOfSegments[1], GPIO_PIN_SET);
		else if(showY)
			HAL_GPIO_WritePin(GPIOG, tableOfSegments[2], GPIO_PIN_SET);
		else if(showZ)
			HAL_GPIO_WritePin(GPIOG, tableOfSegments[3], GPIO_PIN_SET);
		return;
	}
	int digitToShow;
	if(strcmp(digitName, "first") == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
		if(showX)
			makeDigitFromFloatValue(1, x, &digitToShow);
		else if(showY)
			makeDigitFromFloatValue(1, y, &digitToShow);
		else if(showZ)
			makeDigitFromFloatValue(1, z, &digitToShow);
		HAL_GPIO_WritePin(GPIOG, tableOfSegments[digitToShow] | GPIO_PIN_9, GPIO_PIN_SET);

	}
	else if(strcmp(digitName, "second") == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
		if(showX)
			makeDigitFromFloatValue(2, x, &digitToShow);
		else if(showY)
			makeDigitFromFloatValue(2, y, &digitToShow);
		else if(showZ)
			makeDigitFromFloatValue(2, z, &digitToShow);
		HAL_GPIO_WritePin(GPIOG, tableOfSegments[digitToShow], GPIO_PIN_SET);

	}
	else if(strcmp(digitName, "third") == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
		if(showX)
			makeDigitFromFloatValue(3, x, &digitToShow);
		else if(showY)
			makeDigitFromFloatValue(3, y, &digitToShow);
		else if(showZ)
			makeDigitFromFloatValue(3, z, &digitToShow);
		HAL_GPIO_WritePin(GPIOG, tableOfSegments[digitToShow], GPIO_PIN_SET);

	}
}


/* USER CODE END 1 */

