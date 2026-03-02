/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f7xx_hal.h"

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
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart8;
extern UART_HandleTypeDef huart2;
//extern DMA_HandleTypeDef hdma_uart7_rx;
//extern DMA_HandleTypeDef hdma_uart7_tx;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart6_rx;
extern DMA_HandleTypeDef hdma_usart6_tx;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart4_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;


/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR14A_Pin GPIO_PIN_2
#define MOTOR14A_GPIO_Port GPIOE
#define MOTOR16A_Pin GPIO_PIN_3
#define MOTOR16A_GPIO_Port GPIOE
#define DI21_Pin GPIO_PIN_4
#define DI21_GPIO_Port GPIOE
#define DI18_Pin GPIO_PIN_5
#define DI18_GPIO_Port GPIOE
#define DI5_Pin GPIO_PIN_6
#define DI5_GPIO_Port GPIOE
#define MOTOR17A_Pin GPIO_PIN_8
#define MOTOR17A_GPIO_Port GPIOI
#define MOTOR21_EN_Pin GPIO_PIN_13
#define MOTOR21_EN_GPIO_Port GPIOC
#define DI23_Pin GPIO_PIN_9
#define DI23_GPIO_Port GPIOI
#define DI13_Pin GPIO_PIN_10
#define DI13_GPIO_Port GPIOI
#define MOTOR1A_Pin GPIO_PIN_0
#define MOTOR1A_GPIO_Port GPIOF
#define MOTOR2A_Pin GPIO_PIN_1
#define MOTOR2A_GPIO_Port GPIOF
#define MOTOR1_EN_Pin GPIO_PIN_2
#define MOTOR1_EN_GPIO_Port GPIOF
#define MOTOR2_EN_Pin GPIO_PIN_3
#define MOTOR2_EN_GPIO_Port GPIOF
#define MOTOR1B_Pin GPIO_PIN_4
#define MOTOR1B_GPIO_Port GPIOF
#define MOTOR2B_Pin GPIO_PIN_5
#define MOTOR2B_GPIO_Port GPIOF
#define MOTOR21B_Pin GPIO_PIN_6
#define MOTOR21B_GPIO_Port GPIOF
#define MOTOR22A_Pin GPIO_PIN_7
#define MOTOR22A_GPIO_Port GPIOF
#define MOTOR22_EN_Pin GPIO_PIN_8
#define MOTOR22_EN_GPIO_Port GPIOF
#define MOTOR22B_Pin GPIO_PIN_9
#define MOTOR22B_GPIO_Port GPIOF
#define MOTOR5_EN_Pin GPIO_PIN_0
#define MOTOR5_EN_GPIO_Port GPIOC
#define MOTOR13B_Pin GPIO_PIN_2
#define MOTOR13B_GPIO_Port GPIOC
#define MOTOR21A_Pin GPIO_PIN_0
#define MOTOR21A_GPIO_Port GPIOA
#define DI9_Pin GPIO_PIN_1
#define DI9_GPIO_Port GPIOA
#define DI10_Pin GPIO_PIN_2
#define DI10_GPIO_Port GPIOA
#define DI14_Pin GPIO_PIN_2
#define DI14_GPIO_Port GPIOH
#define DI1_Pin GPIO_PIN_3
#define DI1_GPIO_Port GPIOH
#define MOTOR20A_Pin GPIO_PIN_4
#define MOTOR20A_GPIO_Port GPIOH
#define MOTOR20_EN_Pin GPIO_PIN_5
#define MOTOR20_EN_GPIO_Port GPIOH
#define RS4852_RX_Pin GPIO_PIN_3
#define RS4852_RX_GPIO_Port GPIOA
#define MOTOR14_EN_Pin GPIO_PIN_4
#define MOTOR14_EN_GPIO_Port GPIOA
#define MOTOR23A_Pin GPIO_PIN_5
#define MOTOR23A_GPIO_Port GPIOA
#define MOTOR15_EN_Pin GPIO_PIN_6
#define MOTOR15_EN_GPIO_Port GPIOA
#define DI3_Pin GPIO_PIN_4
#define DI3_GPIO_Port GPIOC
#define DI8_Pin GPIO_PIN_5
#define DI8_GPIO_Port GPIOC
#define DI2_Pin GPIO_PIN_0
#define DI2_GPIO_Port GPIOB
#define DI17_Pin GPIO_PIN_1
#define DI17_GPIO_Port GPIOB
#define MOTOR5B_Pin GPIO_PIN_11
#define MOTOR5B_GPIO_Port GPIOF
#define MOTOR3A_Pin GPIO_PIN_12
#define MOTOR3A_GPIO_Port GPIOF
#define MOTOR4A_Pin GPIO_PIN_13
#define MOTOR4A_GPIO_Port GPIOF
#define MOTOR3_EN_Pin GPIO_PIN_14
#define MOTOR3_EN_GPIO_Port GPIOF
#define MOTOR4_EN_Pin GPIO_PIN_15
#define MOTOR4_EN_GPIO_Port GPIOF
#define MOTOR3B_Pin GPIO_PIN_0
#define MOTOR3B_GPIO_Port GPIOG
#define MOTOR4B_Pin GPIO_PIN_1
#define MOTOR4B_GPIO_Port GPIOG
#define MOTOR12B_Pin GPIO_PIN_7
#define MOTOR12B_GPIO_Port GPIOE
#define DI11_Pin GPIO_PIN_8
#define DI11_GPIO_Port GPIOE
#define MOTOR12_EN_Pin GPIO_PIN_9
#define MOTOR12_EN_GPIO_Port GPIOE
#define MOTOR9A_Pin GPIO_PIN_10
#define MOTOR9A_GPIO_Port GPIOE
#define MOTOR9_EN_Pin GPIO_PIN_11
#define MOTOR9_EN_GPIO_Port GPIOE
#define MOTOR9B_Pin GPIO_PIN_12
#define MOTOR9B_GPIO_Port GPIOE
#define MOTOR10A_Pin GPIO_PIN_13
#define MOTOR10A_GPIO_Port GPIOE
#define MOTOR10_EN_Pin GPIO_PIN_14
#define MOTOR10_EN_GPIO_Port GPIOE
#define MOTOR10B_Pin GPIO_PIN_15
#define MOTOR10B_GPIO_Port GPIOE
#define MOTOR23_EN_Pin GPIO_PIN_10
#define MOTOR23_EN_GPIO_Port GPIOB
#define DI6_Pin GPIO_PIN_11
#define DI6_GPIO_Port GPIOB
#define MOTOR6A_Pin GPIO_PIN_6
#define MOTOR6A_GPIO_Port GPIOH
#define MOTOR7_EN_Pin GPIO_PIN_7
#define MOTOR7_EN_GPIO_Port GPIOH
#define DI15_Pin GPIO_PIN_8
#define DI15_GPIO_Port GPIOH
#define MOTOR18_EN_Pin GPIO_PIN_9
#define MOTOR18_EN_GPIO_Port GPIOH
#define MOTOR13_EN_Pin GPIO_PIN_12
#define MOTOR13_EN_GPIO_Port GPIOB
#define MOTOR20B_Pin GPIO_PIN_13
#define MOTOR20B_GPIO_Port GPIOB
#define MOTOR19_EN_Pin GPIO_PIN_14
#define MOTOR19_EN_GPIO_Port GPIOB
#define MOTOR19B_Pin GPIO_PIN_15
#define MOTOR19B_GPIO_Port GPIOB
#define MOTOR18B_Pin GPIO_PIN_11
#define MOTOR18B_GPIO_Port GPIOD
#define MOTOR18A_Pin GPIO_PIN_12
#define MOTOR18A_GPIO_Port GPIOD
#define MOTOR7B_Pin GPIO_PIN_14
#define MOTOR7B_GPIO_Port GPIOD
#define MOTOR8A_Pin GPIO_PIN_15
#define MOTOR8A_GPIO_Port GPIOD
#define MOTOR5A_Pin GPIO_PIN_2
#define MOTOR5A_GPIO_Port GPIOG
#define MOTOR17_EN_Pin GPIO_PIN_3
#define MOTOR17_EN_GPIO_Port GPIOG
#define MOTOR6B_Pin GPIO_PIN_4
#define MOTOR6B_GPIO_Port GPIOG
#define MOTOR7A_Pin GPIO_PIN_5
#define MOTOR7A_GPIO_Port GPIOG
#define DI4_Pin GPIO_PIN_6
#define DI4_GPIO_Port GPIOG
#define DI24_Pin GPIO_PIN_7
#define DI24_GPIO_Port GPIOG
#define RS4851_TX_Pin GPIO_PIN_6
#define RS4851_TX_GPIO_Port GPIOC
#define RS4851_RX_Pin GPIO_PIN_7
#define RS4851_RX_GPIO_Port GPIOC
#define MOTOR24B_Pin GPIO_PIN_8
#define MOTOR24B_GPIO_Port GPIOC
#define MOTOR24A_Pin GPIO_PIN_9
#define MOTOR24A_GPIO_Port GPIOC
#define MOTOR15B_Pin GPIO_PIN_8
#define MOTOR15B_GPIO_Port GPIOA
#define DI16_Pin GPIO_PIN_11
#define DI16_GPIO_Port GPIOA
#define DI19_Pin GPIO_PIN_13
#define DI19_GPIO_Port GPIOH
#define MOTOR23B_Pin GPIO_PIN_14
#define MOTOR23B_GPIO_Port GPIOH
#define DI20_Pin GPIO_PIN_15
#define DI20_GPIO_Port GPIOH
#define DI7_Pin GPIO_PIN_0
#define DI7_GPIO_Port GPIOI
#define RS4851_EN_Pin GPIO_PIN_1
#define RS4851_EN_GPIO_Port GPIOI
#define DO4_Pin GPIO_PIN_3
#define DO4_GPIO_Port GPIOI
#define MOTOR11_EN_Pin GPIO_PIN_15
#define MOTOR11_EN_GPIO_Port GPIOA
#define LORA2_TX_Pin GPIO_PIN_10
#define LORA2_TX_GPIO_Port GPIOC
#define LORA2_RX_Pin GPIO_PIN_11
#define LORA2_RX_GPIO_Port GPIOC
#define MOTOR8_EN_Pin GPIO_PIN_0
#define MOTOR8_EN_GPIO_Port GPIOD
#define MOTOR8B_Pin GPIO_PIN_1
#define MOTOR8B_GPIO_Port GPIOD
#define MOTOR24_EN_Pin GPIO_PIN_2
#define MOTOR24_EN_GPIO_Port GPIOD
#define MOTOR16B_Pin GPIO_PIN_3
#define MOTOR16B_GPIO_Port GPIOD
#define MOTOR19A_Pin GPIO_PIN_4
#define MOTOR19A_GPIO_Port GPIOD
#define RS4852_TX_Pin GPIO_PIN_5
#define RS4852_TX_GPIO_Port GPIOD
#define MOTOR11B_Pin GPIO_PIN_7
#define MOTOR11B_GPIO_Port GPIOD
#define MOTOR17B_Pin GPIO_PIN_9
#define MOTOR17B_GPIO_Port GPIOG
#define SCSn_Pin GPIO_PIN_10
#define SCSn_GPIO_Port GPIOG
#define RSTn_Pin GPIO_PIN_11
#define RSTn_GPIO_Port GPIOG
#define INTn_Pin GPIO_PIN_12
#define INTn_GPIO_Port GPIOG
#define MOTOR6_EN_Pin GPIO_PIN_15
#define MOTOR6_EN_GPIO_Port GPIOG
#define MOTOR12A_Pin GPIO_PIN_3
#define MOTOR12A_GPIO_Port GPIOB
#define MOTOR13A_Pin GPIO_PIN_4
#define MOTOR13A_GPIO_Port GPIOB
#define MOTOR11A_Pin GPIO_PIN_5
#define MOTOR11A_GPIO_Port GPIOB
#define RS4852_EN_Pin GPIO_PIN_8
#define RS4852_EN_GPIO_Port GPIOB
#define DI12_Pin GPIO_PIN_9
#define DI12_GPIO_Port GPIOB
#define SG_RX_Pin GPIO_PIN_0
#define SG_RX_GPIO_Port GPIOE
#define SG_TX_Pin GPIO_PIN_1
#define SG_TX_GPIO_Port GPIOE
#define DI22_Pin GPIO_PIN_4
#define DI22_GPIO_Port GPIOI
#define MOTOR15A_Pin GPIO_PIN_5
#define MOTOR15A_GPIO_Port GPIOI
#define MOTOR16_EN_Pin GPIO_PIN_6
#define MOTOR16_EN_GPIO_Port GPIOI
#define MOTOR14B_Pin GPIO_PIN_7
#define MOTOR14B_GPIO_Port GPIOI

/* USER CODE BEGIN Private defines */
#define LoraDataLength 38
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
