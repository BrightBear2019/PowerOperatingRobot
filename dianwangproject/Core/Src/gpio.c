/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, MOTOR14A_Pin|MOTOR16A_Pin|MOTOR9A_Pin|MOTOR9_EN_Pin
                          |MOTOR9B_Pin|MOTOR10A_Pin|MOTOR10_EN_Pin|MOTOR10B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, MOTOR17A_Pin|RS4851_EN_Pin|DO4_Pin|MOTOR15A_Pin
                          |MOTOR16_EN_Pin|MOTOR14B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MOTOR21_EN_Pin|MOTOR5_EN_Pin|MOTOR13B_Pin|MOTOR24B_Pin
                          |MOTOR24A_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, MOTOR1A_Pin|MOTOR2A_Pin|MOTOR1_EN_Pin|MOTOR2_EN_Pin
                          |MOTOR1B_Pin|MOTOR2B_Pin|MOTOR21B_Pin|MOTOR22A_Pin
                          |MOTOR22_EN_Pin|MOTOR22B_Pin|MOTOR5B_Pin|MOTOR3A_Pin
                          |MOTOR4A_Pin|MOTOR3_EN_Pin|MOTOR4_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, MOTOR21A_Pin|MOTOR14_EN_Pin|MOTOR23A_Pin|MOTOR15_EN_Pin
                          |MOTOR15B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOH, MOTOR20A_Pin|MOTOR20_EN_Pin|MOTOR6A_Pin|MOTOR7_EN_Pin
                          |MOTOR18_EN_Pin|MOTOR23B_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, MOTOR3B_Pin|MOTOR4B_Pin|MOTOR5A_Pin|MOTOR17_EN_Pin
                          |MOTOR6B_Pin|MOTOR7A_Pin|MOTOR17B_Pin|MOTOR6_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, MOTOR12B_Pin|MOTOR12_EN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MOTOR23_EN_Pin|MOTOR13_EN_Pin|MOTOR20B_Pin|MOTOR19_EN_Pin
                          |MOTOR19B_Pin|MOTOR12A_Pin|MOTOR13A_Pin|RS4852_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, MOTOR18B_Pin|MOTOR7B_Pin|MOTOR8A_Pin|MOTOR8_EN_Pin
                          |MOTOR8B_Pin|MOTOR24_EN_Pin|MOTOR16B_Pin|MOTOR19A_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, MOTOR18A_Pin|MOTOR11B_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MOTOR11_EN_GPIO_Port, MOTOR11_EN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, SCSn_Pin|RSTn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MOTOR11A_GPIO_Port, MOTOR11A_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : MOTOR14A_Pin MOTOR16A_Pin MOTOR12B_Pin MOTOR12_EN_Pin
                           MOTOR9A_Pin MOTOR9_EN_Pin MOTOR9B_Pin MOTOR10A_Pin
                           MOTOR10_EN_Pin MOTOR10B_Pin */
  GPIO_InitStruct.Pin = MOTOR14A_Pin|MOTOR16A_Pin|MOTOR12B_Pin|MOTOR12_EN_Pin
                          |MOTOR9A_Pin|MOTOR9_EN_Pin|MOTOR9B_Pin|MOTOR10A_Pin
                          |MOTOR10_EN_Pin|MOTOR10B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : DI21_Pin DI18_Pin DI5_Pin DI11_Pin */
  GPIO_InitStruct.Pin = DI21_Pin|DI18_Pin|DI5_Pin|DI11_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR17A_Pin RS4851_EN_Pin DO4_Pin */
  GPIO_InitStruct.Pin = MOTOR17A_Pin|RS4851_EN_Pin|DO4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : MOTOR21_EN_Pin */
  GPIO_InitStruct.Pin = MOTOR21_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MOTOR21_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DI23_Pin DI13_Pin DI7_Pin DI22_Pin */
  GPIO_InitStruct.Pin = DI23_Pin|DI13_Pin|DI7_Pin|DI22_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR1A_Pin MOTOR2A_Pin MOTOR1_EN_Pin MOTOR2_EN_Pin
                           MOTOR1B_Pin MOTOR2B_Pin MOTOR21B_Pin MOTOR22A_Pin
                           MOTOR22_EN_Pin MOTOR22B_Pin MOTOR5B_Pin MOTOR3A_Pin
                           MOTOR4A_Pin MOTOR3_EN_Pin MOTOR4_EN_Pin */
  GPIO_InitStruct.Pin = MOTOR1A_Pin|MOTOR2A_Pin|MOTOR1_EN_Pin|MOTOR2_EN_Pin
                          |MOTOR1B_Pin|MOTOR2B_Pin|MOTOR21B_Pin|MOTOR22A_Pin
                          |MOTOR22_EN_Pin|MOTOR22B_Pin|MOTOR5B_Pin|MOTOR3A_Pin
                          |MOTOR4A_Pin|MOTOR3_EN_Pin|MOTOR4_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR5_EN_Pin MOTOR13B_Pin MOTOR24B_Pin MOTOR24A_Pin */
  GPIO_InitStruct.Pin = MOTOR5_EN_Pin|MOTOR13B_Pin|MOTOR24B_Pin|MOTOR24A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR21A_Pin MOTOR14_EN_Pin MOTOR23A_Pin MOTOR15_EN_Pin
                           MOTOR15B_Pin MOTOR11_EN_Pin */
  GPIO_InitStruct.Pin = MOTOR21A_Pin|MOTOR14_EN_Pin|MOTOR23A_Pin|MOTOR15_EN_Pin
                          |MOTOR15B_Pin|MOTOR11_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DI9_Pin DI10_Pin DI16_Pin */
  GPIO_InitStruct.Pin = DI9_Pin|DI10_Pin|DI16_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DI14_Pin DI1_Pin DI15_Pin DI19_Pin
                           DI20_Pin */
  GPIO_InitStruct.Pin = DI14_Pin|DI1_Pin|DI15_Pin|DI19_Pin
                          |DI20_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR20A_Pin MOTOR20_EN_Pin MOTOR6A_Pin MOTOR7_EN_Pin
                           MOTOR18_EN_Pin MOTOR23B_Pin */
  GPIO_InitStruct.Pin = MOTOR20A_Pin|MOTOR20_EN_Pin|MOTOR6A_Pin|MOTOR7_EN_Pin
                          |MOTOR18_EN_Pin|MOTOR23B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : DI3_Pin DI8_Pin */
  GPIO_InitStruct.Pin = DI3_Pin|DI8_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : DI2_Pin DI17_Pin DI6_Pin DI12_Pin */
  GPIO_InitStruct.Pin = DI2_Pin|DI17_Pin|DI6_Pin|DI12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR3B_Pin MOTOR4B_Pin MOTOR5A_Pin MOTOR17_EN_Pin
                           MOTOR6B_Pin MOTOR7A_Pin MOTOR17B_Pin MOTOR6_EN_Pin */
  GPIO_InitStruct.Pin = MOTOR3B_Pin|MOTOR4B_Pin|MOTOR5A_Pin|MOTOR17_EN_Pin
                          |MOTOR6B_Pin|MOTOR7A_Pin|MOTOR17B_Pin|MOTOR6_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR23_EN_Pin MOTOR13_EN_Pin MOTOR20B_Pin MOTOR19_EN_Pin
                           MOTOR19B_Pin MOTOR12A_Pin MOTOR13A_Pin MOTOR11A_Pin
                           RS4852_EN_Pin */
  GPIO_InitStruct.Pin = MOTOR23_EN_Pin|MOTOR13_EN_Pin|MOTOR20B_Pin|MOTOR19_EN_Pin
                          |MOTOR19B_Pin|MOTOR12A_Pin|MOTOR13A_Pin|MOTOR11A_Pin
                          |RS4852_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR18B_Pin MOTOR18A_Pin MOTOR7B_Pin MOTOR8A_Pin
                           MOTOR8_EN_Pin MOTOR8B_Pin MOTOR24_EN_Pin MOTOR16B_Pin
                           MOTOR19A_Pin MOTOR11B_Pin */
  GPIO_InitStruct.Pin = MOTOR18B_Pin|MOTOR18A_Pin|MOTOR7B_Pin|MOTOR8A_Pin
                          |MOTOR8_EN_Pin|MOTOR8B_Pin|MOTOR24_EN_Pin|MOTOR16B_Pin
                          |MOTOR19A_Pin|MOTOR11B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : DI4_Pin DI24_Pin */
  GPIO_InitStruct.Pin = DI4_Pin|DI24_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : SCSn_Pin RSTn_Pin */
  GPIO_InitStruct.Pin = SCSn_Pin|RSTn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : INTn_Pin */
  GPIO_InitStruct.Pin = INTn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INTn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR15A_Pin MOTOR16_EN_Pin MOTOR14B_Pin */
  GPIO_InitStruct.Pin = MOTOR15A_Pin|MOTOR16_EN_Pin|MOTOR14B_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */


void Motor_Control(MotorType motor, DirectionType direction) 
{
    GPIO_PinState in1, in2 ,ENA;
    switch(direction) 
		{
        case REVERSE://
					  ENA = GPIO_PIN_SET;   //1
            in1 = GPIO_PIN_RESET; //0
            in2 = GPIO_PIN_SET;   //1
            break;
        case FORWARD://
					  ENA = GPIO_PIN_SET;   //1    
            in1 = GPIO_PIN_SET;   //1
            in2 = GPIO_PIN_RESET; //0
            break;
				case STOP://
					  ENA = GPIO_PIN_RESET; //0
            in1 = GPIO_PIN_SET;
            in2 = GPIO_PIN_RESET;
            break;
        case BRAKE://
				  	ENA = GPIO_PIN_SET;   //1 
            in1 = GPIO_PIN_SET;
            in2 = GPIO_PIN_SET;
        default:  //
					  ENA = GPIO_PIN_SET;   //1 
            in1 = GPIO_PIN_RESET;
            in2 = GPIO_PIN_RESET;
            break;
    }

    if(motor == MOTOR1) 
		{
			  HAL_GPIO_WritePin(MOTOR1_EN_GPIO_Port,MOTOR1_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR1A_GPIO_Port,MOTOR1A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR1B_GPIO_Port,MOTOR1B_Pin,in2);
			
    }else if(motor == MOTOR2)
		{
        HAL_GPIO_WritePin(MOTOR2_EN_GPIO_Port,MOTOR2_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR2A_GPIO_Port,MOTOR2A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR2B_GPIO_Port,MOTOR2B_Pin,in2);
    }else if(motor == MOTOR3)
		{
        HAL_GPIO_WritePin(MOTOR3_EN_GPIO_Port,MOTOR3_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR3A_GPIO_Port,MOTOR3A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR3B_GPIO_Port,MOTOR3B_Pin,in2);
    }else if(motor == MOTOR4)
		{
        HAL_GPIO_WritePin(MOTOR4_EN_GPIO_Port,MOTOR4_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR4A_GPIO_Port,MOTOR4A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR4B_GPIO_Port,MOTOR4B_Pin,in2);
    }else if(motor == MOTOR5)
		{
        HAL_GPIO_WritePin(MOTOR5_EN_GPIO_Port,MOTOR5_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR5A_GPIO_Port,MOTOR5A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR5B_GPIO_Port,MOTOR5B_Pin,in2);
    }else if(motor == MOTOR6)
		{
        HAL_GPIO_WritePin(MOTOR6_EN_GPIO_Port,MOTOR6_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR6A_GPIO_Port,MOTOR6A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR6B_GPIO_Port,MOTOR6B_Pin,in2);
    }else if(motor == MOTOR7)
		{
        HAL_GPIO_WritePin(MOTOR7_EN_GPIO_Port,MOTOR7_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR7A_GPIO_Port,MOTOR7A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR7B_GPIO_Port,MOTOR7B_Pin,in2);
    }else if(motor == MOTOR8)
		{
        HAL_GPIO_WritePin(MOTOR8_EN_GPIO_Port,MOTOR8_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR8A_GPIO_Port,MOTOR8A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR8B_GPIO_Port,MOTOR8B_Pin,in2);
    }else if(motor == MOTOR9)
		{
        HAL_GPIO_WritePin(MOTOR9_EN_GPIO_Port,MOTOR9_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR9A_GPIO_Port,MOTOR9A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR9B_GPIO_Port,MOTOR9B_Pin,in2);
    }else if(motor == MOTOR10)
		{
        HAL_GPIO_WritePin(MOTOR10_EN_GPIO_Port,MOTOR10_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR10A_GPIO_Port,MOTOR10A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR10B_GPIO_Port,MOTOR10B_Pin,in2);
    }else if(motor == MOTOR11)
		{
        HAL_GPIO_WritePin(MOTOR11_EN_GPIO_Port,MOTOR11_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR11A_GPIO_Port,MOTOR11A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR11B_GPIO_Port,MOTOR11B_Pin,in2);
    }else if(motor == MOTOR12)
		{
        HAL_GPIO_WritePin(MOTOR12_EN_GPIO_Port,MOTOR21_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR12A_GPIO_Port,MOTOR12A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR12B_GPIO_Port,MOTOR12B_Pin,in2);
    }else if(motor == MOTOR13)
		{
        HAL_GPIO_WritePin(MOTOR13_EN_GPIO_Port,MOTOR13_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR13A_GPIO_Port,MOTOR13A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR13B_GPIO_Port,MOTOR13B_Pin,in2);
    }else if(motor == MOTOR14)
		{
        HAL_GPIO_WritePin(MOTOR14_EN_GPIO_Port,MOTOR14_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR14A_GPIO_Port,MOTOR14A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR14B_GPIO_Port,MOTOR14B_Pin,in2);
    }else if(motor == MOTOR15)
		{
        HAL_GPIO_WritePin(MOTOR15_EN_GPIO_Port,MOTOR15_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR15A_GPIO_Port,MOTOR15A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR15B_GPIO_Port,MOTOR15B_Pin,in2);
    }else if(motor == MOTOR16)
		{
        HAL_GPIO_WritePin(MOTOR16_EN_GPIO_Port,MOTOR16_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR16A_GPIO_Port,MOTOR16A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR16B_GPIO_Port,MOTOR16B_Pin,in2);
    }else if(motor == MOTOR17)
		{
        HAL_GPIO_WritePin(MOTOR17_EN_GPIO_Port,MOTOR17_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR17A_GPIO_Port,MOTOR17A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR17B_GPIO_Port,MOTOR17B_Pin,in2);
    }else if(motor == MOTOR18)
		{
        HAL_GPIO_WritePin(MOTOR18_EN_GPIO_Port,MOTOR18_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR18A_GPIO_Port,MOTOR18A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR18B_GPIO_Port,MOTOR18B_Pin,in2);
    }else if(motor == MOTOR19)
		{
        HAL_GPIO_WritePin(MOTOR19_EN_GPIO_Port,MOTOR19_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR19A_GPIO_Port,MOTOR19A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR19B_GPIO_Port,MOTOR19B_Pin,in2);
    }else if(motor == MOTOR20)
		{
        HAL_GPIO_WritePin(MOTOR20_EN_GPIO_Port,MOTOR20_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR20A_GPIO_Port,MOTOR20A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR20B_GPIO_Port,MOTOR20B_Pin,in2);
    }else if(motor == MOTOR21)
		{
        HAL_GPIO_WritePin(MOTOR21_EN_GPIO_Port,MOTOR21_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR21A_GPIO_Port,MOTOR21A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR21B_GPIO_Port,MOTOR21B_Pin,in2);
    }else if(motor == MOTOR22)
		{
        HAL_GPIO_WritePin(MOTOR22_EN_GPIO_Port,MOTOR22_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR22A_GPIO_Port,MOTOR22A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR22B_GPIO_Port,MOTOR22B_Pin,in2);
    }else if(motor == MOTOR23)
		{
        HAL_GPIO_WritePin(MOTOR23_EN_GPIO_Port,MOTOR23_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR23A_GPIO_Port,MOTOR23A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR23B_GPIO_Port,MOTOR23B_Pin,in2);
    }else if(motor == MOTOR24)
		{
        HAL_GPIO_WritePin(MOTOR24_EN_GPIO_Port,MOTOR24_EN_Pin,ENA);
			  HAL_GPIO_WritePin(MOTOR24A_GPIO_Port,MOTOR24A_Pin,in1);
			  HAL_GPIO_WritePin(MOTOR24B_GPIO_Port,MOTOR24B_Pin,in2);
    }
		
}



/* USER CODE END 2 */
