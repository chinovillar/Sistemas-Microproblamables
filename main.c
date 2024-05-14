/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

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

/* USER CODE BEGIN PV */
int i=0;                        /*variable para contar*/
int tres_segundos=720000;    /*número equivalente a 3 segundos según frecuencia del clock*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
int funcion_contador();     /* Función que cuenta el tiempo para cerrar la puera*/
void cerrar_puerta();       /* Función que cierra la puerta*/
void abrir_puerta();        /* Función que abre la puerta*/
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (HAL_GPIO_ReadPin (GPIOB, Tec3_Pin) == (GPIO_PIN_SET) && HAL_GPIO_ReadPin(GPIOB, Tec1_Pin) == (GPIO_PIN_RESET))/*Si la puerta está totalmente abierta y no hay presencia, empieza a contar el contador*/
	  {
		  funcion_contador(i); /*llamado a la función que aumenta el contador*/
		  i=funcion_contador(i);
		  if (i >= tres_segundos) /*cuanto el contador llega a 3 segundos, llama a la función que cierra la puerta*/
		  {
			  cerrar_puerta();
		  }
	   }
	  else /*en caso de que puerta no esté completamente abierta o si hay presencia*/
	  {
		  i=0; /*se resetea el contador a cero*/
	  }
	  if (HAL_GPIO_ReadPin(GPIOB, Tec1_Pin) == (GPIO_PIN_SET)) /*si se detecta presencia*/
	  {
		  abrir_puerta(); /*llama a la función para abrir la puerta*/
	  }



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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Led1_Pin|Led2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Led1_Pin Led2_Pin */
  GPIO_InitStruct.Pin = Led1_Pin|Led2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Tec1_Pin Tec2_Pin Tec3_Pin */
  GPIO_InitStruct.Pin = Tec1_Pin|Tec2_Pin|Tec3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
int funcion_contador(i)
{
	i=i+1;
	return i;

}
void cerrar_puerta()
{
	while (HAL_GPIO_ReadPin (GPIOB, Tec1_Pin)!= (GPIO_PIN_SET) && (HAL_GPIO_ReadPin (GPIOB, Tec2_Pin)!= GPIO_PIN_SET))/*en caso de no haber presencia y que la puerta no llegue a final de carrera cerrada*/
	{
		HAL_GPIO_WritePin (GPIOB, Led1_Pin, GPIO_PIN_RESET); /*dirección del motor -> cerrando*/
		HAL_GPIO_WritePin (GPIOB, Led2_Pin, GPIO_PIN_SET); /*estado del motor -> encendido*/
	}

	/*caso de que se detecte presencia o se llegue al final de carrera cerrado*/
    HAL_GPIO_WritePin (GPIOB, Led2_Pin, GPIO_PIN_RESET); /*estado del motor -> apagado*/


}

void abrir_puerta()
{
	if ((HAL_GPIO_ReadPin (GPIOB, Tec3_Pin))!=(GPIO_PIN_SET)) /*en caso de no se detecte el final de carrera abierto*/
	{
		HAL_GPIO_WritePin (GPIOB, Led1_Pin, GPIO_PIN_SET);/*dirección del motor -> abriendo*/
		HAL_GPIO_WritePin (GPIOB, Led2_Pin, GPIO_PIN_SET); /*estado del motor -> encendido*/
	}
	else /*en caso de que se detecte fin de carrea abierto*/
	{
		HAL_GPIO_WritePin (GPIOB, Led2_Pin, GPIO_PIN_RESET); /*estado del motor -> apagado*/
	}

}


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
