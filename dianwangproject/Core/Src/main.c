/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "string.h"
#include <stdbool.h>
#include "user_main.h"

#include <stdio.h>
#include <stdint.h>
#include "wizchip_conf.h"
#include "wiz_interface.h"
#include "loopback.h"
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//舵机指令
uint8_t sg_reset[]={0XFA,0X00,0XFB,0XFB,0XFE};
uint8_t sg_cotdata[]={0XFA,0X00,0X00,0X00,0XFE};

//控制指令
uint8_t HeartPulse[] = {0x06,0xAA,0x53, 0x54,0x4D,0x33,0x32,0x46,0x31,0x30,0x33,0x63,0x63};//心跳包

uint8_t SMLimitCmd[]={0x0B,0x03,0x03,0x0A,0x00,0x02,0xE4,0xE7};//读步步进限位
uint8_t SMPositionCmd[]={0x09,0x03,0x03,0x10,0x00,0x02,0xC4,0xC2};//读步进位置
uint8_t GPSCmd[]={0x31,0x03,0x00,0xCF,0x00,0x06,0xF0,0x07};//读GPS数据
uint8_t HeightCmd[]={0x16,0x03,0x00,0x04,0x00,0x01,0xC6,0xEC};//读激光测距传感器（平台距地面高度）
uint8_t LiftCmd[]={0x18,0x03,0x02,0x01,0x00,0x01,0xD6,0x7B};//读TOF测距传感器（升降台)
uint8_t BoPiCmd[]={0xA2,0x03,0xA2,0x00,0x00,0x0D,0xBF,0x24};//剥皮器读指令
uint8_t SGCmd[]={0xFA,0x00,0x00,0x5A,0xFE};//舵机指令
uint8_t Lora2Set[]={0xC0,0x00, 0x65, 0x18, 0x49, 0x1c};//剥皮器读指令

uint8_t LcaCmd[] = {0x04,0x03,0x00,0x00,0x00,0x03,0x05,0x9E};//读平台角度
//uint8_t LcaCmd[] = {0x04,0x03,0x00,0x02,0x00,0x07,0xA5,0x9D};	//读平台角度:RPY+温度
//uint8_t HeightCmd[]={0x16,0x03,0x00,0x04,0x00,0x01,0xC6,0xEC};//读激光测距传感器（平台高度）
uint8_t Height20Cmd[] = {0x20,0x03,0x00,0x34,0x00,0x01,0xC3,0x75};	//读平台距挂钩高度
uint8_t Height21Cmd[] = {0x21,0x03,0x00,0x34,0x00,0x01,0xC2,0xA4};	//读平台距挂钩高度
uint8_t Height22Cmd[] = {0x22,0x03,0x00,0x34,0x00,0x01,0xC2,0x97};	//读平台距主线高度
uint8_t Height23Cmd[] = {0x23,0x03,0x00,0x34,0x00,0x01,0xC3,0x46};	//读平台距主线高度
uint8_t PressureSensorCmd[]={0x30,0x03,0x00,0x00,0x00,0x01,0x80,0x2B};	//读压线钳压力传感器
uint8_t TakePressureSensorCmd[]={0x31,0x03,0x00,0x00,0x00,0x02,0xC1,0xFB};	//读送给器压力传感器
uint8_t TakePressureSensorSetZeroCmd[] = {0x31,0x06,0x00,0x35,0x00,0x05,0x5C,0x37};//送给器压力传感器校准零点

uint8_t Lora1_Redata[50];//lora1接受数组缓冲区
uint8_t Lora2_Redata[50];//lora2接受数组缓冲区
uint8_t RS4851_Redata[80];//RS4851接受数组缓冲区
uint8_t RS4852_Redata[80];//RS4852接受数组缓冲区
uint8_t Usart1_Redata[36];//ttl串口1接受数据缓冲区
uint8_t Usart3_Redata[36];//ttl串口1接受数据缓冲区


//for RS4852 handler
extern uint8_t recv_cmd[50];
extern uint16_t recv_length;
extern uint8_t isControlCmdReceived;

uint8_t AngleSV[]={0xFA,0x00,0xFD,
		                 0x00,0x00,0x00,0x78,
										 0x78,0x00,0x00,0x00,												
										 0x5A,0x30,0x3C,0x00,
										 0x00,0x00,0x00,0x00,
										 0x00,0x00,0x00,0x00,
	                   0xFE};
//Lora 发送数据包
										 
unsigned char Send_data[LoraDataLength];

//stm32通讯方式
uint8_t CommMode;//0-lora  1-wifi

										 
extern uint16_t uart6_rx_size;								 
					
extern uint16_t local_port;
extern uint8_t ethernet_buf[ETHERNET_BUF_MAX_SIZE];


uint8_t  tcp_buff[512];  //tcp接受数组
uint16_t tcp_len;          
uint8_t  TCP_Recved=0;   //tcp接受标志位   




										 

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART6_UART_Init();
  MX_USART1_UART_Init();
  MX_UART8_Init();
  MX_USART2_UART_Init();
  MX_UART4_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_SPI2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

	SG_init();		//舵机初始化	
	HAL_TIM_Base_Start_IT(&htim3);//开启定时器
	
  Send_data[0] =0x06;
  Send_data[1] =0xFF;										//Lora:0x00; Wifi:0x01
	for(int i = 2;i<LoraDataLength;i++)
		 Send_data[i] = 0x00;

	HAL_UARTEx_ReceiveToIdle_IT(&huart1,Usart1_Redata,sizeof(Usart1_Redata));
	HAL_UARTEx_ReceiveToIdle_IT(&huart6,RS4851_Redata,sizeof(RS4851_Redata));
	HAL_UARTEx_ReceiveToIdle_IT(&huart2,RS4852_Redata,sizeof(RS4852_Redata));	
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3,Lora1_Redata,sizeof(Lora1_Redata));	
	HAL_UARTEx_ReceiveToIdle_IT(&huart4,Lora2_Redata,sizeof(Lora2_Redata));
  __HAL_DMA_DISABLE_IT(&hdma_usart3_rx,DMA_IT_HT);//关闭DMA接受过半中断

	wifi_init();
	CommMode = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
//		Lora1_SendData(Height20Cmd, 8);  //LOAR1
//		HAL_Delay(1000);
		
		
//		Motor_Control(MOTOR1, 1);
//		HAL_Delay(1000);
//		Motor_Control(MOTOR1, 1);
//		HAL_Delay(1000);
		
		
		//loopback_tcps(SOCKET_ID, tcp_buff, local_port);
		do_tcp_server(SOCKET_ID, tcp_buff, local_port);
	
		
		
    /* USER CODE END WHILE */

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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
