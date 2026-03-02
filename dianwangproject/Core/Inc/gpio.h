/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

// ï¿½ï¿½ï¿½ï¿½ï¿½Å¶ï¿½ï¿½ï¿½
typedef enum {
    MOTOR1 = 0,
    MOTOR2,
	  MOTOR3,
	  MOTOR4,
		MOTOR5,
		MOTOR6,
		MOTOR7,
		MOTOR8,
		MOTOR9,
		MOTOR10,
		MOTOR11,
		MOTOR12,
		MOTOR13,
		MOTOR14,
		MOTOR15,
		MOTOR16,
		MOTOR17,
		MOTOR18,
		MOTOR19,
	  MOTOR20,
	  MOTOR21,
	  MOTOR22,
	  MOTOR23,
	  MOTOR24
} MotorType;

// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
typedef enum {
    BRAKE = 0,
    FORWARD,
    REVERSE,
	  STOP

	
} DirectionType;

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?  ï¿½ï¿½ï¿½ï¿½1ï¿½ï¿½ï¿½ï¿½ï¿? ï¿½ï¿½ï¿½ï¿½2 ×´Ì¬
void Motor_Control(MotorType motor, DirectionType direction);




/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

