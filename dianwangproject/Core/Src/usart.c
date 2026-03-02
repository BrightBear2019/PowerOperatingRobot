/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "socket.h"
#include "user_main.h"
#include <stdint.h>
#include <math.h>

extern uint8_t  rx_4851_flag ;	



HAL_StatusTypeDef Lora1_SendData(uint8_t *pData, uint16_t Size)
{
	return HAL_UART_Transmit_DMA(&huart3,pData,Size);
}
HAL_StatusTypeDef Lora2_SendData(uint8_t *pData, uint16_t Size)
{
	return HAL_UART_Transmit_DMA(&huart4,pData,Size);
}




void SG_Reset(void)
{
	uint8_t sg_reset[]={0XFA,0X00,0XFB,0XFB,0XFE};
	HAL_UART_Transmit_IT(&huart8,sg_reset,5);
	while (__HAL_UART_GET_FLAG(&huart8, UART_FLAG_TC) == RESET); 
	
}

//void SG_SetAngle(uint8_t channel,uint8_t angle)
//{	 
//	  uint8_t sg_data[]={0XFA,0X00,0XFB,0XFB,0XFE};
//    if (channel > 24) channel = 0;
//    if (angle > 180) angle = 180;
//		sg_data[2]=channel;
//    sg_data[3]=angle;
//		
//		AngleSV[channel+3] = angle;
//		
//		HAL_UART_Transmit_IT(&huart8,sg_data,5);
//	  while (__HAL_UART_GET_FLAG(&huart8, UART_FLAG_TC) == RESET); 
//				
//}


void SG_SetAngle(uint8_t channel,uint8_t angle)
{	 
//	  uint8_t sg_data[]={0XFA,0X00,0XFB,0XFB,0XFE};
    if (channel > 24) channel = 0;
    if (angle > 180) angle = 180;
//		sg_data[2]=channel;
//    sg_data[3]=angle;
//		
//		AngleSV[channel+3] = angle;
//		
//		HAL_UART_Transmit_IT(&huart8,sg_data,5);
//	  while (__HAL_UART_GET_FLAG(&huart8, UART_FLAG_TC) == RESET); 
		
		AngleSV[channel+3] = angle;
		SG_SetAllAngle(AngleSV);
				
}


void SG_SetAllAngle(uint8_t *angles)
{
		HAL_UART_Transmit_IT(&huart8,angles,24);
	  while (__HAL_UART_GET_FLAG(&huart8, UART_FLAG_TC) == RESET); 

}

void SG_init(void)
{
	SG_SetAngle(0x00,0x00);//SG_INSUL1 	 0
	SG_SetAngle(0x01,0x00);//SG_INSUL2   0
	SG_SetAngle(0x02,0x00);//SG_WINCH1       0
	SG_SetAngle(0x03,0x78);//SG_WINCH2      120  
	SG_SetAngle(0x04,0x78);//SG_WINCH3       120
	SG_SetAngle(0x05,0x00);//SG_WINCH4      0
  SG_SetAngle(0x06,0x3c);//SG_OPEN1        90
	SG_SetAngle(0x07,0x3c);//SG_OPEN2       90
	SG_SetAngle(0x08,0x5A);//SG_OPEN2        90
	SG_SetAngle(0x09,0x3c);//SG_OPEN2        90
	
	
}

void Cover_Open()	
{
	AngleSV[9] = 0x00;
  AngleSV[10] = 0x00;
										 
	SG_SetAllAngle(AngleSV);
										 
	
}
void Cover_Close()	
{
	AngleSV[9] = 0x3c;
  AngleSV[10] = 0x3c;
	SG_SetAllAngle(AngleSV);
	
	
}
void Wheel_Out()
{
		
		AngleSV[5] = 0x78;
		AngleSV[6] = 0x00;
		AngleSV[7] = 0x00;
		AngleSV[8] = 0x78;
		SG_SetAllAngle(AngleSV);

}
void Wheel_In()
{
		AngleSV[5] = 0x00;
		AngleSV[6] = 0x78;
		AngleSV[7] = 0x78;
		AngleSV[8] = 0x00;
		SG_SetAllAngle(AngleSV);
	
}

void Insul_Out(void)
{
		AngleSV[3] = 0x96;
		AngleSV[4] = 0x79;
		SG_SetAllAngle(AngleSV);
		
}

void Insul_In(void)
{

		AngleSV[3] = 0x02;
		AngleSV[4] = 0x02;
		SG_SetAllAngle(AngleSV);
}


/* USER CODE END 0 */

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart8;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
UART_HandleTypeDef huart6;
DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_uart4_tx;
DMA_HandleTypeDef hdma_uart8_tx;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;
DMA_HandleTypeDef hdma_usart6_rx;
DMA_HandleTypeDef hdma_usart6_tx;

/* UART4 init function */
void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 9600;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}
/* UART8 init function */
void MX_UART8_Init(void)
{

  /* USER CODE BEGIN UART8_Init 0 */

  /* USER CODE END UART8_Init 0 */

  /* USER CODE BEGIN UART8_Init 1 */

  /* USER CODE END UART8_Init 1 */
  huart8.Instance = UART8;
  huart8.Init.BaudRate = 9600;
  huart8.Init.WordLength = UART_WORDLENGTH_8B;
  huart8.Init.StopBits = UART_STOPBITS_1;
  huart8.Init.Parity = UART_PARITY_NONE;
  huart8.Init.Mode = UART_MODE_TX_RX;
  huart8.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart8.Init.OverSampling = UART_OVERSAMPLING_16;
  huart8.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart8.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart8) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART8_Init 2 */

  /* USER CODE END UART8_Init 2 */

}
/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

   RS4852_RX_EN();
	
	
	
  /* USER CODE END USART2_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  huart6.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart6.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */
	
   RS4851_RX_EN();
  /* USER CODE END USART6_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspInit 0 */

  /* USER CODE END UART4_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART4;
    PeriphClkInitStruct.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* UART4 clock enable */
    __HAL_RCC_UART4_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**UART4 GPIO Configuration
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX
    */
    GPIO_InitStruct.Pin = LORA2_TX_Pin|LORA2_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* UART4 DMA Init */
    /* UART4_RX Init */
    hdma_uart4_rx.Instance = DMA1_Stream2;
    hdma_uart4_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_uart4_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_uart4_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_uart4_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_uart4_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_uart4_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_uart4_rx.Init.Mode = DMA_NORMAL;
    hdma_uart4_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_uart4_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_uart4_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_uart4_rx);

    /* UART4_TX Init */
    hdma_uart4_tx.Instance = DMA1_Stream4;
    hdma_uart4_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_uart4_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_uart4_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_uart4_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_uart4_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_uart4_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_uart4_tx.Init.Mode = DMA_NORMAL;
    hdma_uart4_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_uart4_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_uart4_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_uart4_tx);

    /* UART4 interrupt Init */
    HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
  /* USER CODE BEGIN UART4_MspInit 1 */

  /* USER CODE END UART4_MspInit 1 */
  }
  else if(uartHandle->Instance==UART8)
  {
  /* USER CODE BEGIN UART8_MspInit 0 */

  /* USER CODE END UART8_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART8;
    PeriphClkInitStruct.Uart8ClockSelection = RCC_UART8CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* UART8 clock enable */
    __HAL_RCC_UART8_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    /**UART8 GPIO Configuration
    PE0     ------> UART8_RX
    PE1     ------> UART8_TX
    */
    GPIO_InitStruct.Pin = SG_RX_Pin|SG_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_UART8;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /* UART8 DMA Init */
    /* UART8_TX Init */
    hdma_uart8_tx.Instance = DMA1_Stream0;
    hdma_uart8_tx.Init.Channel = DMA_CHANNEL_5;
    hdma_uart8_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_uart8_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_uart8_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_uart8_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_uart8_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_uart8_tx.Init.Mode = DMA_NORMAL;
    hdma_uart8_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_uart8_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_uart8_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_uart8_tx);

    /* UART8 interrupt Init */
    HAL_NVIC_SetPriority(UART8_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(UART8_IRQn);
  /* USER CODE BEGIN UART8_MspInit 1 */

  /* USER CODE END UART8_MspInit 1 */
  }
  else if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA2_Stream2;
    hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA2_Stream7;
    hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA3     ------> USART2_RX
    PD5     ------> USART2_TX
    */
    GPIO_InitStruct.Pin = RS4852_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(RS4852_RX_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = RS4852_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(RS4852_TX_GPIO_Port, &GPIO_InitStruct);

    /* USART2 DMA Init */
    /* USART2_RX Init */
    hdma_usart2_rx.Instance = DMA1_Stream5;
    hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_NORMAL;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart2_rx);

    /* USART2_TX Init */
    hdma_usart2_tx.Instance = DMA1_Stream6;
    hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart2_tx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3;
    PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* USART3 DMA Init */
    /* USART3_RX Init */
    hdma_usart3_rx.Instance = DMA1_Stream1;
    hdma_usart3_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_rx.Init.Mode = DMA_NORMAL;
    hdma_usart3_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart3_rx);

    /* USART3_TX Init */
    hdma_usart3_tx.Instance = DMA1_Stream3;
    hdma_usart3_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart3_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart3_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart3_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart3_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart3_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart3_tx.Init.Mode = DMA_NORMAL;
    hdma_usart3_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart3_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart3_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart3_tx);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART6;
    PeriphClkInitStruct.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
    */
    GPIO_InitStruct.Pin = RS4851_TX_Pin|RS4851_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART6 DMA Init */
    /* USART6_RX Init */
    hdma_usart6_rx.Instance = DMA2_Stream1;
    hdma_usart6_rx.Init.Channel = DMA_CHANNEL_5;
    hdma_usart6_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart6_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart6_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart6_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart6_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart6_rx.Init.Mode = DMA_NORMAL;
    hdma_usart6_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_usart6_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart6_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart6_rx);

    /* USART6_TX Init */
    hdma_usart6_tx.Instance = DMA2_Stream6;
    hdma_usart6_tx.Init.Channel = DMA_CHANNEL_5;
    hdma_usart6_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart6_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart6_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart6_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart6_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart6_tx.Init.Mode = DMA_NORMAL;
    hdma_usart6_tx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_usart6_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart6_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart6_tx);

    /* USART6 interrupt Init */
    HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==UART4)
  {
  /* USER CODE BEGIN UART4_MspDeInit 0 */

  /* USER CODE END UART4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART4_CLK_DISABLE();

    /**UART4 GPIO Configuration
    PC10     ------> UART4_TX
    PC11     ------> UART4_RX
    */
    HAL_GPIO_DeInit(GPIOC, LORA2_TX_Pin|LORA2_RX_Pin);

    /* UART4 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* UART4 interrupt Deinit */
    HAL_NVIC_DisableIRQ(UART4_IRQn);
  /* USER CODE BEGIN UART4_MspDeInit 1 */

  /* USER CODE END UART4_MspDeInit 1 */
  }
  else if(uartHandle->Instance==UART8)
  {
  /* USER CODE BEGIN UART8_MspDeInit 0 */

  /* USER CODE END UART8_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_UART8_CLK_DISABLE();

    /**UART8 GPIO Configuration
    PE0     ------> UART8_RX
    PE1     ------> UART8_TX
    */
    HAL_GPIO_DeInit(GPIOE, SG_RX_Pin|SG_TX_Pin);

    /* UART8 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* UART8 interrupt Deinit */
    HAL_NVIC_DisableIRQ(UART8_IRQn);
  /* USER CODE BEGIN UART8_MspDeInit 1 */

  /* USER CODE END UART8_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA3     ------> USART2_RX
    PD5     ------> USART2_TX
    */
    HAL_GPIO_DeInit(RS4852_RX_GPIO_Port, RS4852_RX_Pin);

    HAL_GPIO_DeInit(RS4852_TX_GPIO_Port, RS4852_TX_Pin);

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PD8     ------> USART3_TX
    PD9     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_8|GPIO_PIN_9);

    /* USART3 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();

    /**USART6 GPIO Configuration
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX
    */
    HAL_GPIO_DeInit(GPIOC, RS4851_TX_Pin|RS4851_RX_Pin);

    /* USART6 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void RS4851_SendByte(  uint8_t ch )
{
	  RS4851_TX_EN();//使能发送
    HAL_UART_Transmit(&huart6, (uint8_t *)&ch, 1, 0xFFFF);	
	  
	  RS4851_RX_EN();//	使能接受
}
void RS4851_SendBuf( uint8_t *buf,uint16_t len)
{
   	unsigned int k=0;	
	  RS4851_TX_EN();//使能发送
    do 
    {
        HAL_UART_Transmit(&huart6, (uint8_t *)&buf[k], 1, 100);//已修改0xFFFF为100.
        k++;
    } while(k < len);
		
	
		RS485_delay(0xFFF);
		RS4851_RX_EN();//	使能接受
	
}
void RS4852_SendByte(  uint8_t ch )
{
	  RS4852_TX_EN();//	
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
	  RS4852_RX_EN();
}

void RS4852_SendBuf( uint8_t *buf,uint16_t len)//
{
		
   	unsigned int k=0;	
	  RS4852_TX_EN();//	  
    do 
    {
        HAL_UART_Transmit(&huart2, (uint8_t *)&buf[k], 1, 0xFFFF);
        k++;
    } while(k < len);
		RS485_delay(0xFFF);/*加短暂延时，保证485发送数据完毕*/
		RS4852_RX_EN();
		
}

extern uint8_t isCalibrationRequested;
extern uint8_t isWeightSetZeroRequested;
extern uint8_t recv_cmd[50];
extern uint16_t recv_length;
extern uint8_t isControlCmdReceived;

void parseLora1Cmd(uint8_t *Lora_Redata,uint16_t nlength)
{

		 if(Lora_Redata[0]!=0x06||nlength<=4)		//非有效指令
				return;			
		 
     if(nlength>50)
				return;
     
		 //uint8_t cmd[50];
		 for(int i =0;i<nlength-4;i++)
				recv_cmd[i] = Lora_Redata[i+2];
		 recv_length = nlength - 4;
		 
    if(Lora_Redata[1]==0x00)
		{
				CommMode = Lora_Redata[2]; 
			  HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据				
		}

     if(CommMode==1)	//Wifi 通讯模式
				return;
			
     switch(Lora_Redata[1])
     {
			 case 0xAA:		  //心跳包
				 //Lora2_SendData(HeartPulse,13);
			   HAL_UART_Transmit_DMA(&huart3,HeartPulse,13);//	
			   //HAL_UART_Transmit_DMA(&huart3, Lora1_Redata, nlength);
				 break;
			 case 0xFF:		  //空中平台状态数据
				 //Lora1_SendData(Send_data,38);
			    //HAL_UART_Transmit_DMA(&huart3,Send_data,38);
			  HAL_UART_Transmit_DMA(&huart3,Send_data,LoraDataLength);//TTL
				 break;
			case 0x02:			//压线钳	
				HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据
				 break;
			case 0x03:			//步进电机				 
				 RS4852_SendBuf(recv_cmd,nlength-4);
			   //isControlCmdReceived = 1;
				  if(recv_cmd[1]==0x06)		//只回传控制指令
						HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据;
				 break;				
			case 0x04:			//电推杆
				Motor_Control(recv_cmd[0],recv_cmd[1]);
				HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据
				 break;				
			case 0x05:			//小升降平台
				HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据
				 break;		
			case 0x07:			//舵机控制				
			//HAL_UART_Transmit_DMA(&huart1,Lora_Redata,nlength);//TTL
				if(Lora_Redata[2]==0x10)
				{
					 Cover_Open(); 	
					HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据
					break;	
				}
				if(Lora_Redata[2]==0x11)
				{
					 Cover_Close(); 
					HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据
					break;	
				}
				if(Lora_Redata[2]==0x12)
				{
					 Wheel_Out(); 	
					HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据
					break;	
				}
				 if(Lora_Redata[2]==0x13)
				{
					 Wheel_In();		
					HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据
					break;	 
				}
				SG_SetAngle(Lora_Redata[2],Lora_Redata[3]);
				HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//返回响应数据
				 break;	
			case 0x08:
			     isCalibrationRequested = 1;	
					break;
			case 0x09:
			     isWeightSetZeroRequested = 1;	
			     break;
			
			 default:
				 break;
		 }		 
}

void parseTCPCmd(uint8_t *TCP_Redata,uint16_t nlength)
{

	 if(TCP_Redata[0]!=0x06||nlength<=4)		
				return;			
		 
     if(nlength>50)
				return;
     
		 uint8_t cmd[50];
		 for(int i =0;i<nlength-4;i++)
				cmd[i] = TCP_Redata[i+2];

		if(TCP_Redata[1]==0x00)
		{
				CommMode = TCP_Redata[2]; 
			  send(SOCKET_ID, TCP_Redata,nlength);
		}

     switch(TCP_Redata[1])
     {
			 case 0xAA:		
			   //HAL_UART_Transmit_DMA(&huart3,HeartPulse,13);
			   send(SOCKET_ID, HeartPulse,13);
				 break;
			 case 0xFF:		 
			  //HAL_UART_Transmit_DMA(&huart3,Send_data,38);//TTL
			  send(SOCKET_ID, Send_data,LoraDataLength);
				 break;
			case 0x02:				
				//HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);//
			  send(SOCKET_ID, TCP_Redata,nlength);
				 break;
			case 0x03:					 
				 RS4852_SendBuf(cmd,nlength-4);
			   if(cmd[1]==0x06) 
					send(SOCKET_ID, TCP_Redata,nlength);
				 //HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);
				 break;				
			case 0x04:			
			   //HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);
		   		Motor_Control(cmd[0],cmd[1]);
					send(SOCKET_ID, TCP_Redata,nlength);
				 break;				
			case 0x05:			
				//HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);
			  send(SOCKET_ID, TCP_Redata,nlength);
				 break;		
			case 0x07:					
			//HAL_UART_Transmit_DMA(&huart1,Lora_Redata,nlength);//TTL
				if(TCP_Redata[2]==0x10)
				{
					 Cover_Open(); 	
					//HAL_UART_Transmit_DMA(&huart3,TCP_Redata,nlength);
					send(SOCKET_ID, TCP_Redata,nlength);
					break;	
				}
				if(TCP_Redata[2]==0x11)
				{
					 Cover_Close(); 
					//HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);
					send(SOCKET_ID, TCP_Redata,nlength);
					break;	
				}
				if(TCP_Redata[2]==0x12)
				{
					 Wheel_Out(); 	
					//HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);
					send(SOCKET_ID, TCP_Redata,nlength);
					break;	
				}
				 if(TCP_Redata[2]==0x13)
				{
					 Wheel_In();		
					//HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);
					send(SOCKET_ID, TCP_Redata,nlength);
					break;	 
				}
				SG_SetAngle(TCP_Redata[2],TCP_Redata[3]);
				//HAL_UART_Transmit_DMA(&huart3,Lora_Redata,nlength);
				send(SOCKET_ID, TCP_Redata,nlength);
				 break;	
			case 0x08:
			       isCalibrationRequested = 1;	
					break;
			case 0x09:
			     isWeightSetZeroRequested = 1;	
			     break;
			 default:
				 break;
		 }		 
}


//解析STM32_RS4851接收到的数据(传感器)
void parseRS4851( uint8_t *buf,uint16_t len) 
{
	//CRC16校验
	uint16_t RollAngle,PitchAngle,YawAngle;
	int32_t decimal_value; 
	uint16_t isPositive = 0; 
	
	uint16_t tempCRC, receiveCRC;
	tempCRC= ModbusCRC16(buf, len-2); // 计算接收数据的校验码
  receiveCRC=buf[len-2]*256 + buf[len -1];
	if(tempCRC==receiveCRC) 
	{
		if(buf[1]==0x03)
		{
			switch(buf[0])
			{
				case 0x04://LCA
					Send_data[2] = buf[3];
					Send_data[3] = buf[4];
					Send_data[4] = buf[5];
					Send_data[5] = buf[6];		
					Send_data[6] = buf[7];	
					Send_data[7] = buf[8];	
										
					//采用扩充数据区SendData[38-51]
					//for(int i =38;i<LoraDataLength;i++)
					 // Send_data[i] = buf[i-35];
		 
					break;
				case 0x03://Climatedecimal_value

					break;
				case 0x07://步进---多个步进，03返回数据格式一致，同一驱动器如何区分那个轴？
					if(buf[2]==0x02)//限位
						Send_data[22] = buf[4];
					if(buf[2]==0x04)//位置
					{
						Send_data[23] = buf[3];
						Send_data[24] = buf[4];
						Send_data[25] = buf[5];
						Send_data[26] = buf[6];
					}				
					break;
				case 0x16:  //读激光测距传感器（平台高度）
					Send_data[14] = buf[3];
					Send_data[15] = buf[4];
					break;
				case 0x18:  //读激光测距传感器（小升降平台高度）
					//Send_data[16] = buf[3];
					//Send_data[17] = buf[4];
					break;
				case 0x32: //GPS
					Send_data[30] = buf[3];
					Send_data[31] = buf[4];
					Send_data[32] = buf[5];
					Send_data[33] = buf[6];
					Send_data[34] = buf[7];
					Send_data[35] = buf[8];
          break;
				case 0x20://挂钩测距传感器
					Send_data[30] = buf[3];	
				  Send_data[31] = buf[4];	
				   break;
				case 0x21://挂钩测距传感器
					Send_data[32] = buf[3];	
				  Send_data[33] = buf[4];
				  break;
				case 0x22://挂钩测距传感器
					Send_data[34] = buf[3];	
				  Send_data[35] = buf[4];	
				  break;
				case 0x23://挂钩测距传感器
					Send_data[36] = buf[3];	
				  Send_data[37] = buf[4];
				  break;
				case 0x31://送给器压力
					Send_data[16] = buf[5];	
				  Send_data[17] = buf[6];
				  break;
				default:
					break;	
			}
		}
	}
	return;
}



//解析STM32_RS4852接收到的数据(步进电机：位置，限位)
//读状态字返回数据格式一样，无法判断哪一个轴。
void parseRS4852( uint8_t *buf,uint16_t len)
{
	//CRC16校验
	uint16_t tempCRC, receiveCRC;
	tempCRC= ModbusCRC16(buf, len-2); // 计算接收数据的校验码
  receiveCRC=buf[len-2]*256 + buf[len -1];
	
	if(tempCRC==receiveCRC) 
	{
		if(buf[1]==0x03)
		{
			switch(buf[0])
			{
				case 0x07:
					if(buf[1]==0x03)//轴1状态控制字
						Send_data[11] |= (1 << 0);
					break;
				case 0x08:
					if(buf[1]==0x03&&buf[2]==0x02
						)//轴1状态控制字
						Send_data[11] |= (1 << 2);
					break;
					
				case 0x09://行走步进位置
					if(buf[1]==0x03&&buf[2]==0x04)//位置
					{
						Send_data[23] = buf[3];
						Send_data[24] = buf[4];
						Send_data[25] = buf[5];
						Send_data[26] = buf[6];
					}		
					if(buf[1]==0x03&&buf[2]==0x02)//状态控制字
						Send_data[11] |= (1 << 4);  // 将第3位置1（位编号从0开始）
					break;
				case 0x0B://行走电推杆步进电机限位
					if(buf[2]==0x04)//限位
						Send_data[22] = ((buf[4] & 0x0F) << 4) | (buf[6] & 0x0F);		
					
					if(buf[1]==0x03&&buf[2]==0x02)//状态控制字
						Send_data[11] |= (1 << 6);  // 将第3位置1（位编号从0开始）
					break;	

				default:
					break;			
			}
	
		}
	}
}

//void parseRS4852( uint8_t *buf,uint16_t len)
//{

//	uint16_t tempCRC, receiveCRC;
//	tempCRC= ModbusCRC16(buf, len-2); 
//  receiveCRC=buf[len-2]*256 + buf[len -1];
//	if(tempCRC==receiveCRC) 
//	{
//		if(buf[1]==0x03)
//		{
//			switch(buf[0])
//			{
//				case 0x05:
//					if(buf[2]==0x04)
//					{
//						Send_data[23] = buf[3];
//						Send_data[24] = buf[4];
//						Send_data[25] = buf[5];
//						Send_data[26] = buf[6];
//					}					
//					break;
//				case 0x0B:
//					if(buf[2]==0x04)
//						Send_data[22] = ((buf[4] & 0x0F) << 4) | (buf[6] & 0x0F);		
//					break;	
//					default:
//					break;	
//			
//			}
//	
//		}
//	}
//}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) 
{
    if(huart->Instance == USART1)//TTL
	  {
      HAL_UART_Transmit_IT(&huart1, RS4851_Redata, Size );
			
	  }
	  else if(huart->Instance == USART6)//RS4851
	  {
	 
		  //HAL_UART_Transmit_IT(&huart1, RS4851_Redata, Size);
			parseRS4851(RS4851_Redata,Size);
	  }
	  else if(huart->Instance == USART2)//RS4852
	  {
			parseRS4852(RS4852_Redata,Size);
	  }	
		else if(huart->Instance == UART4)//LORA2
		{
		
		}
		else if(huart->Instance == USART3)//USART3:LORA1
		{
			//HAL_UART_Transmit_IT(&huart1, Lora1_Redata,Size);
      parseLora1Cmd(Lora1_Redata,Size);
		}
		HAL_UARTEx_ReceiveToIdle_IT(&huart1,Usart1_Redata,sizeof(Usart1_Redata));
		
		HAL_UARTEx_ReceiveToIdle_IT(&huart6,RS4851_Redata,sizeof(RS4851_Redata));
		HAL_UARTEx_ReceiveToIdle_IT(&huart2,RS4852_Redata,sizeof(RS4852_Redata));	
		HAL_UARTEx_ReceiveToIdle_DMA(&huart3,Lora1_Redata,sizeof(Lora1_Redata));	
		HAL_UARTEx_ReceiveToIdle_IT(&huart4,Lora2_Redata,sizeof(Lora2_Redata));
		__HAL_DMA_DISABLE_IT(&hdma_usart3_rx,DMA_IT_HT);
		
}


#define SEND_MODE   GPIO_PIN_SET
#define RECV_MODE   GPIO_PIN_RESET



    



/* USER CODE END 1 */
