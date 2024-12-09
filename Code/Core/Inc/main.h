/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DP_SEG_Pin GPIO_PIN_0
#define DP_SEG_GPIO_Port GPIOA
#define G_SEG_Pin GPIO_PIN_1
#define G_SEG_GPIO_Port GPIOA
#define F_SEG_Pin GPIO_PIN_2
#define F_SEG_GPIO_Port GPIOA
#define E_SEG_Pin GPIO_PIN_3
#define E_SEG_GPIO_Port GPIOA
#define D_SEG_Pin GPIO_PIN_4
#define D_SEG_GPIO_Port GPIOA
#define C_SEG_Pin GPIO_PIN_5
#define C_SEG_GPIO_Port GPIOA
#define B_SEG_Pin GPIO_PIN_6
#define B_SEG_GPIO_Port GPIOA
#define A_SEG_Pin GPIO_PIN_7
#define A_SEG_GPIO_Port GPIOA
#define Down_Key_Pin GPIO_PIN_0
#define Down_Key_GPIO_Port GPIOB
#define Down_Key_EXTI_IRQn EXTI0_1_IRQn
#define ENT_Key_Pin GPIO_PIN_1
#define ENT_Key_GPIO_Port GPIOB
#define ENT_Key_EXTI_IRQn EXTI0_1_IRQn
#define RST_Key_Pin GPIO_PIN_2
#define RST_Key_GPIO_Port GPIOB
#define RST_Key_EXTI_IRQn EXTI2_3_IRQn
#define D1_Pin GPIO_PIN_8
#define D1_GPIO_Port GPIOA
#define Up_Key_Pin GPIO_PIN_6
#define Up_Key_GPIO_Port GPIOC
#define Up_Key_EXTI_IRQn EXTI4_15_IRQn
#define D4_Pin GPIO_PIN_11
#define D4_GPIO_Port GPIOA
#define ESC_Key_Pin GPIO_PIN_12
#define ESC_Key_GPIO_Port GPIOA
#define ESC_Key_EXTI_IRQn EXTI4_15_IRQn
#define CD_Key_Pin GPIO_PIN_15
#define CD_Key_GPIO_Port GPIOA
#define CD_Key_EXTI_IRQn EXTI4_15_IRQn
#define D2_Pin GPIO_PIN_3
#define D2_GPIO_Port GPIOB
#define OD_Key_Pin GPIO_PIN_4
#define OD_Key_GPIO_Port GPIOB
#define OD_Key_EXTI_IRQn EXTI4_15_IRQn
#define LED_Select_Pin GPIO_PIN_5
#define LED_Select_GPIO_Port GPIOB
#define D3_Pin GPIO_PIN_6
#define D3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
