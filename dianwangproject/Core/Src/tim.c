/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
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
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "usart.h"
#include "wiz_platform.h"
#include "wizchip_conf.h"
#include "wiz_interface.h"

extern uint8_t LcaCmd[];
extern uint8_t HeightCmd[];
extern uint8_t Height20Cmd[];	
extern uint8_t Height21Cmd[];	
extern uint8_t Height22Cmd[];	
extern uint8_t Height23Cmd[];	
extern uint8_t SMLimitCmd[];
extern uint8_t SMPositionCmd[];
extern uint8_t PressureSensorCmd[];
extern uint8_t TakePressureSensorCmd[];
extern uint8_t TakePressureSensorSetZeroCmd[];

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 216-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}
/* TIM3 init function */
void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 21600-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    //HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
		HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();

    /* TIM3 interrupt Init */
    //HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
		HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();

    /* TIM3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM3_IRQn);
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
extern unsigned char Send_data[LoraDataLength];

volatile uint8_t timerCount = 1;  //定时中断计数器


// 全局变量定义
typedef enum {
    NORMAL_SENDING,        // 正常发送状态
    CALIBRATION_START,     // 校准开始状态
    CALIBRATION_WAIT_3S,   // 3秒等待状态
    CALIBRATION_SEND_CMD, // 发送cdm1状态
    CALIBRATION_WAIT_5S,    // 5秒等待状态
	  RS4852_SEND_CMD					//发送Lora接收到的485_2总线上设备控制指令
} SystemState_t;

SystemState_t systemState = NORMAL_SENDING;
SystemState_t systemState2 = NORMAL_SENDING;
uint32_t calibrationStartTime = 0;
uint8_t isCalibrationRequested = 0;
uint8_t isWeightSetZeroRequested = 0;


uint8_t cdm1[]={0x04,0x06,0x00,0x53,0x00,0x67,0X38,0X64};//校准X-y轴
uint8_t cdm2[]={0x04,0x06,0x00,0x54,0x00,0x52,0X49,0XB2};//校准z轴
uint8_t SetLCAZZERO[]={0x04,0x06,0x00,0x15,0x00,0xFF,0xD8,0x1B};//LCA航向角清零
uint8_t SetLCAXYZERO[]={0x04,0x06,0x00,0x15,0x00,0xFF,0xD8,0x1B};//LCA XY角清零
		
								
uint8_t lastTick = 0;
//volatile uint8_t timerCounter = 1;  //定时中断计数器
uint8_t isControlCmdReceived = 0;

uint8_t recv_cmd[50];
uint16_t recv_length;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim3)
		{
			  //采集24DI状态
	   	  Read_All_DI_States();
			
        // 状态机处理-----传感器数据采集
        switch (systemState) 
				{
            case NORMAL_SENDING:// 正常发送模式
                
                timerCount = (timerCount % 8) + 1;
       
                if (timerCount == 1) 
								{								
									if (isCalibrationRequested) 
									{
											systemState = CALIBRATION_START;
											//RS4851_SendBuf(SetLCAZZERO, 8);
											isCalibrationRequested = 0;  // 重置请求标志																	
									}
									else
										RS4851_SendBuf(LcaCmd, 8);
									
								}
                if (timerCount == 2) RS4851_SendBuf(HeightCmd, 8);
                if (timerCount == 3) RS4851_SendBuf(Height20Cmd, 8);
                if (timerCount == 4) RS4851_SendBuf(Height21Cmd, 8);
						    if (timerCount == 5) RS4851_SendBuf(Height22Cmd, 8);
                if (timerCount == 6) RS4851_SendBuf(Height23Cmd, 8);
								if (timerCount == 7) RS4851_SendBuf(PressureSensorCmd, 8);
								if (timerCount == 8) 
								{
									if ( isWeightSetZeroRequested) 
									{
											RS4851_SendBuf(TakePressureSensorSetZeroCmd, 8);
											isWeightSetZeroRequested = 0;  // 重置请求标志
																	
									}
									else
										RS4851_SendBuf(TakePressureSensorCmd, 8);
							
								}
	        			//if(timerCount%2==0) Read_All_DI_States();
			
                // 检查是否收到校准请求
                //if (isCalibrationRequested) 
								//{
                   // systemState = CALIBRATION_START;
									 // RS4851_SendBuf(SetLCAZZERO, 8);
                   // isCalibrationRequested = 0;  // 重置请求标志
									 // break;								
               // }
								
                break;	
		
            case CALIBRATION_START:
                // 发送cdm2并记录开始时间
                RS4851_SendBuf(cdm2, 8);
                calibrationStartTime = HAL_GetTick();
                systemState = CALIBRATION_WAIT_3S;
                break;
                
            case CALIBRATION_WAIT_3S:
                // 等待3秒后发送cdm1
                if (HAL_GetTick() - calibrationStartTime >= 3000) 
								{
                    RS4851_SendBuf(cdm1, 8);
                    calibrationStartTime = HAL_GetTick(); // 重置计时器
                    systemState = CALIBRATION_WAIT_5S;
                }
                break;
                
            case CALIBRATION_WAIT_5S:
                // 检查是否等待了5秒
                if (HAL_GetTick() - calibrationStartTime >= 5000) {
                    // 5秒等待结束，返回正常发送
                    systemState = NORMAL_SENDING;
                }
                break;
        }
		}
		
		
		
		
		if (htim->Instance == TIM2)
    {
        wiz_timer_handler();
    }
}



// 读取所有DI状态
 void Read_All_DI_States(void)
 {
		Send_data[8] = 0;  // 清零状态字节
		if (HAL_GPIO_ReadPin(DI1_GPIO_Port,DI1_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[8] |= (1 << 0); // 设置对应位为1
		}
    if (HAL_GPIO_ReadPin(DI2_GPIO_Port,DI2_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[8] |= (1 << 1); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI3_GPIO_Port,DI3_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[8] |= (1 << 2); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI4_GPIO_Port,DI4_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[8] |= (1 << 3); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI5_GPIO_Port,DI5_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[8] |= (1 << 4); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI6_GPIO_Port,DI6_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[8] |= (1 << 5); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI7_GPIO_Port,DI7_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[8] |= (1 << 6); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI8_GPIO_Port,DI8_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[8] |= (1 << 7); // 设置对应位为1
		}
		
		Send_data[9] = 0;  // 清零状态字节
		if (HAL_GPIO_ReadPin(DI9_GPIO_Port,DI9_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[9] |= (1 << 0); // 设置对应位为1
		}
    if (HAL_GPIO_ReadPin(DI10_GPIO_Port,DI10_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[9] |= (1 << 1); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI11_GPIO_Port,DI11_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[9] |= (1 << 2); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI12_GPIO_Port,DI12_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[9] |= (1 << 3); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI13_GPIO_Port,DI13_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[9] |= (1 << 4); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI14_GPIO_Port,DI14_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[9] |= (1 << 5); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI15_GPIO_Port,DI15_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[9] |= (1 << 6); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI16_GPIO_Port,DI16_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[9] |= (1 << 7); // 设置对应位为1
		}
	
    Send_data[10] = 0;  // 清零状态字节
		if (HAL_GPIO_ReadPin(DI17_GPIO_Port,DI17_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[10] |= (1 << 0); // 设置对应位为1
		}
    if (HAL_GPIO_ReadPin(DI18_GPIO_Port,DI18_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[10] |= (1 << 1); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI19_GPIO_Port,DI19_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[10] |= (1 << 2); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI20_GPIO_Port,DI20_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[10] |= (1 << 3); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI21_GPIO_Port,DI21_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[10] |= (1 << 4); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI22_GPIO_Port,DI22_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[10] |= (1 << 5); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI23_GPIO_Port,DI23_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[10] |= (1 << 6); // 设置对应位为1
		}
		if (HAL_GPIO_ReadPin(DI24_GPIO_Port,DI24_Pin) == GPIO_PIN_RESET) //低电平对应位置1
		{
		  	Send_data[10] |= (1 << 7); // 设置对应位为1
		}
 }




/* USER CODE END 1 */
