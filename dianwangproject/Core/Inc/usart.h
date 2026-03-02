/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "gpio.h"

#include "modbusCRC.h"

extern uint8_t Lora1_Redata[50];//lora1ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½é»ºï¿½ï¿½ï¿½ï¿½
extern uint8_t Lora2_Redata[50];//lora2ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½é»ºï¿½ï¿½ï¿½ï¿½
extern uint8_t RS4851_Redata[80];//RS4851ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½é»ºï¿½ï¿½ï¿½ï¿½
extern uint8_t RS4852_Redata[80];//RS4852ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½é»ºï¿½ï¿½ï¿½ï¿½
extern uint8_t Usart1_Redata[36];//ttlï¿½ï¿½ï¿½ï¿½1ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý»ï¿½ï¿½ï¿½ï¿½ï¿½
extern uint8_t Usart3_Redata[36];//ttlï¿½ï¿½ï¿½ï¿½1ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý»ï¿½ï¿½ï¿½ï¿½ï¿½

extern uint8_t HeartPulse[13];

extern uint8_t AngleSV[24];

//Lora ï¿½ï¿½ï¿½ÍºÍ½ï¿½ï¿½Õµï¿½ï¿½ï¿½ï¿½ï¿½
extern unsigned char Send_data[LoraDataLength];

//ï¿½ï¿½ï¿½Ø»ï¿½ï¿½ï¿½STM32ï¿½ï¿½Í¨Ñ¶Ä£Ê½
extern uint8_t CommMode;//0-loraï¿½ï¿½1-wifi
/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;

extern UART_HandleTypeDef huart8;

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

extern UART_HandleTypeDef huart6;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_UART4_Init(void);
void MX_UART8_Init(void);
void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);
void MX_USART6_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/**********SG**********************************/
void SG_Reset(void);  //
void SG_SetAngle(uint8_t port,uint8_t angle);//

void SG_init(void);			//
void Cover_Open(void);	//
void Cover_Close(void);	//
void Wheel_Out(void);		//
void Wheel_In(void);		//
void Insul_Out(void);		//
void Insul_In(void);		//
void SG_SetAllAngle(uint8_t *angles);

/**********RS485******************************************************************************************/
// ²»¾«È·µÄÑÓÊ±
static void RS485_delay(__IO uint32_t nCount)
{
	for(; nCount != 0; nCount--);
} 
/* 4852Ê¹ÄÜÒý½Å */
// Ê¹ÄÜ485½ÓÊÜÄ£Ê½
#define RS4851_RX_EN()			RS485_delay(1000);\
		HAL_GPIO_WritePin(RS4851_EN_GPIO_Port,RS4851_EN_Pin,GPIO_PIN_RESET); RS485_delay(1000);
// Ê¹ÄÜ485·¢ËÍÄ£Ê½
#define RS4851_TX_EN()			RS485_delay(1000);\
    HAL_GPIO_WritePin(RS4851_EN_GPIO_Port,RS4851_EN_Pin,GPIO_PIN_SET); RS485_delay(1000);




/*  4852Ê¹ÄÜÒý½Å  */
//485½ÓÊÜÄ£Ê½
#define RS4852_RX_EN()			RS485_delay(1000);\
		HAL_GPIO_WritePin(RS4852_EN_GPIO_Port,RS4852_EN_Pin,GPIO_PIN_RESET); RS485_delay(1000);
//485·¢ËÍÄ£Ê½
#define RS4852_TX_EN()			RS485_delay(1000);\
    HAL_GPIO_WritePin(RS4852_EN_GPIO_Port,RS4852_EN_Pin,GPIO_PIN_SET); RS485_delay(1000);
void RS4851_SendByte( uint8_t ch );//4851·¢ËÍÒ»¸ö×Ö½Ú
void RS4851_SendBuf( uint8_t *buf,uint16_t len);//4851·¢ËÍÊý×é
void RS4852_SendByte( uint8_t ch );//4852·¢ËÍÒ»¸ö×Ö½Ú
void RS4852_SendBuf( uint8_t *buf,uint16_t len);//4852·¢ËÍÊý×é

//RS485´¦ÀíÊý¾Ý
void parseRS4851( uint8_t *buf,uint16_t len); //               
void parseRS4852( uint8_t *buf,uint16_t len); //
void parseTCPCmd(uint8_t *TCP_Redata,uint16_t nlength);


/**********LORA******************************************************************************************/

HAL_StatusTypeDef Lora1_SendData(uint8_t *pData, uint16_t Size);  //LOAR1
HAL_StatusTypeDef Lora2_SendData(uint8_t *pData, uint16_t Size);  //LOAR1
void parseLora1Cmd(uint8_t *str,uint16_t nlength);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

