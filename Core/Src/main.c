/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
struct gpsCoordinatesFOJI{
	double lattitude;
	double longtitude;
	double altitude;
};

struct gpsCoordinatesFIJO{
	double lattitude;
	double longtitude;
};

struct eulerAnglesOfPlane{
	float yaw;
	float pitch;
	float roll;
};

//37 ig its acc 48
 struct foji{
	uint8_t start;
	struct gpsCoordinatesFOJI gpsCoord;
	struct eulerAnglesOfPlane anglesOfPlane;
};

 //20 ig its acc 24
struct fijo{
	 uint8_t start;
	_Bool takeoffCommand;
	_Bool qrScanFlag;
	_Bool detectFlag;
	struct gpsCoordinatesFIJO gpsCoord;
};

void sendFOJI(){
	struct foji inTest;
	inTest.start = 0x24; //$
	inTest.gpsCoord.lattitude = 11.11;
	inTest.gpsCoord.longtitude = 22.22;
	inTest.gpsCoord.altitude = 33.33;
	inTest.anglesOfPlane.yaw = 44.44;
	inTest.anglesOfPlane.pitch = 55.55;
	inTest.anglesOfPlane.roll = 66.66;

//	char test = {0xc5,0x07,0x00,0x08};
//	HAL_UART_Transmit(&huart2, test, sizeof(test), HAL_MAX_DELAY);

//	HAL_UART_Transmit(&huart2, &inTest, sizeof(struct foji), HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart2, (uint8_t)sizeof(struct foji), sizeof(sizeof(struct foji)), HAL_MAX_DELAY);

//	HAL_UART_Transmit(&huart2, "TEST ", sizeof("TEST "), HAL_MAX_DELAY);

//	uint8_t buf[sizeof(struct fijo)];
//
//	for(uint16_t i = 0; i < sizeof(struct foji); i++)
//	{
////		if(HAL_UART_Receive(&huart2, &buf[i], 1, HAL_MAX_DELAY) != HAL_OK)
////		{
////			break; //Error receiving data
////		}
//		HAL_UART_Receive(&huart2, &buf[i], 1, HAL_MAX_DELAY);
////		if(i == 1){
////			struct foji *tmp = (struct foji*)buf;
////			if(tmp->start != 0x24){
////				break;
////			}
////		}
//	}
//	struct foji *ptr = (struct foji*)buf;
////	struct foji *ptr = (struct foji*)(uint8_t*)&inTest;
//
////	char buffer[sizeof(struct foji)+1];
////	memcpy(buffer, &inTest, sizeof(struct foji));
////	HAL_UART_Transmit(&huart2, ptr->gpsCoord.longtitude, sizeof(ptr->gpsCoord.longtitude), HAL_MAX_DELAY);
////	HAL_UART_Receive(&huart2, (uint8_t*)&inTest, sizeof(struct foji), HAL_MAX_DELAY);
//	char lon[19];
//	gcvt(ptr->gpsCoord.longtitude, 16, lon);
//	HAL_UART_Transmit(&huart2, lon, strlen(lon), 1000);
//	strcpy(lon,"");

//	char lon[19];
////	double x = sizeof(inTest.start) + sizeof(inTest.anglesOfPlane) + sizeof(inTest.gpsCoord);
//	double x = sizeof(struct fijo);
//	gcvt(x, 6, lon);
////	char lon = x + '0';
//	HAL_UART_Transmit(&huart2, lon, strlen(lon), 1000);
////	strcpy(lon,"");



//	uint8_t buf[] = {'$', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xa3', 's', '~', '\x8a', '\xe3', '8', '&', '@', '.', '\xc9', '\x01', '\xbb', '\x9a', '8','6', '@', 'E', ',', 'b', '\xd8', 'a', '\xaa', '@', '@', '\xb3', '\xc3', '1', 'B', 'V', '4', '^', 'B', '}', 'R', '\x85', 'B', 'a', '\x06', '\x00', '\x08'};
	uint8_t buf[] = {'$', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\xb8', '\x1e', '\x85', '\xeb', 'Q', '8', '&', '@', '\xb8',
			'\x1e', '\x85', '\xeb', 'Q', '8','6', '@', '\n','\xd7','\xa3', 'p','=', '\xaa','@','@', '\x8f', '\xc2', '1', 'B','3',
			'3', '^', 'B', '\xec', 'Q', '\x85', 'B', 'a','\x06', '\x00','\x08'};
//	uint8_t buf[] = {0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa3, 's', '~', 0x8a, 0xe3, '8', '&', '@', '.', 0xc9, 0x01, 0xbb, 0x9a, '8','6', '@', 'E', ',', 'b', 0xd8, 'a', 0xaa, '@', '@', 0xb3, 0xc3, '1', 'B', 'V', '4', '^', 'B', '}', 'R', 0x85, 'B', 'a', 0x06, 0x00, 0x08};

//	for(uint16_t i = 0; i < sizeof(struct foji); i++)
//	{
////		if(HAL_UART_Receive(&huart2, &buf[i], 1, HAL_MAX_DELAY) != HAL_OK)
////		{
////			break; //Error receiving data
////		}
//		HAL_UART_Receive(&huart2, &buf[i], 1, HAL_MAX_DELAY);
////		if(i == 1){
////			struct foji *tmp = (struct foji*)buf;
////			if(tmp->start != 0x24){
////				break;
////			}
////		}
//	}
	struct foji *ptr = (struct foji*)buf;
//	struct foji *ptr = (struct foji*)(uint8_t*)&inTest;

//	char buffer[sizeof(struct foji)+1];
//	memcpy(buffer, &inTest, sizeof(struct foji));
//	HAL_UART_Transmit(&huart2, ptr->gpsCoord.longtitude, sizeof(ptr->gpsCoord.longtitude), HAL_MAX_DELAY);
//	HAL_UART_Receive(&huart2, (uint8_t*)&inTest, sizeof(struct foji), HAL_MAX_DELAY);
	char lon[19];
	HAL_UART_Transmit(&huart2, &ptr->start, sizeof(ptr->start), 1000);
//
	gcvt(ptr->gpsCoord.lattitude, 16, lon);
	HAL_UART_Transmit(&huart2, lon, strlen(lon), 1000);
	strcpy(lon,"");

	gcvt(ptr->gpsCoord.longtitude, 16, lon);
	HAL_UART_Transmit(&huart2, lon, strlen(lon), 1000);
	strcpy(lon,"");

	char lon2[19];
	gcvt(ptr->gpsCoord.altitude, 16, lon2);
	HAL_UART_Transmit(&huart2, lon2, strlen(lon2), 1000);
	strcpy(lon2,"");

	gcvt(ptr->anglesOfPlane.yaw, 4, lon);
	HAL_UART_Transmit(&huart2, lon, strlen(lon), 1000);
	strcpy(lon,"");

	gcvt(ptr->anglesOfPlane.pitch, 4, lon);
	HAL_UART_Transmit(&huart2, lon, strlen(lon), 1000);
	strcpy(lon,"");

	gcvt(ptr->anglesOfPlane.roll, 4, lon);
	HAL_UART_Transmit(&huart2, lon, strlen(lon), 1000);
	strcpy(lon,"");



}

void readFIJO(){
	uint8_t buf[sizeof(struct fijo)];
	buf[0] = 0x24;
	struct fijo in;
	in.start = 0x24;
//	in.detectFlag = 1;
//	in.qrScanFlag = 1;
//	in.takeoffCommand = 1;
//	in.gpsCoord.lattitude = 11.11;
//	in.gpsCoord.longtitude = 22.22;
//	HAL_UART_Transmit(&huart2, &in, sizeof(struct fijo), HAL_MAX_DELAY);
	uint8_t dummy;
	HAL_UART_Receive(&huart2, &dummy, 1, HAL_MAX_DELAY);
	if(dummy == 0x24){
		for(uint16_t i = 1; i < sizeof(struct fijo); i++)
		{
	//		if(HAL_UART_Receive(&huart2, &buf[i], 1, HAL_MAX_DELAY) != HAL_OK)
	//		{
	//			break; //Error receiving data
	//		}
			HAL_UART_Receive(&huart2, &buf[i], 1, HAL_MAX_DELAY);
	//		if(i == 1){
	//			struct fijo *tmp = (struct fijo*)buf;
	//			if(tmp->start != 0x24){
	//				break;
	//			}
	//		}
		}

		struct fijo *ptr = (struct fijo*)buf;
		in.takeoffCommand = ptr->takeoffCommand;
		in.qrScanFlag = ptr->qrScanFlag;
		in.detectFlag = ptr->detectFlag;
		in.gpsCoord.lattitude = ptr->gpsCoord.lattitude;
		in.gpsCoord.longtitude = ptr->gpsCoord.longtitude;
//		HAL_UART_Transmit(&huart2, &in, sizeof(struct fijo), HAL_MAX_DELAY);


		char lon[19];
		HAL_UART_Transmit(&huart2, &ptr->start, sizeof(ptr->start), 1000);
	//
		gcvt(ptr->gpsCoord.lattitude, 16, lon);
		HAL_UART_Transmit(&huart2, lon, strlen(lon), 1000);
		strcpy(lon,"");

		gcvt(ptr->gpsCoord.longtitude, 16, lon);
		HAL_UART_Transmit(&huart2, lon, strlen(lon), 1000);
		strcpy(lon,"");


	}


//	HAL_UART_Receive(&huart2, &buf[0], 1, HAL_MAX_DELAY);
//	HAL_UART_Transmit(&huart2, buf, 1, HAL_MAX_DELAY);

}
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //	  sendFOJI();
    while (1)
    {
      /* USER CODE END WHILE */

      /* USER CODE BEGIN 3 */
    readFIJO();
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

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

