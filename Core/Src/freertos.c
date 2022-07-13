/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../AttitudeManager/Inc/AM_Interface.h"
#include "../../../SensorFusion/Inc/SF_Interface.hpp"
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
/* USER CODE BEGIN Variables */

osThreadId attitudeManagerHandle;
osThreadId sensorFusionHandle;

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

void attitudeManagerExecute(void const *argument);
void sensorFusionExecute(void const *argument);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	/* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {
	/* USER CODE BEGIN Init */

	// attitudeManagerInterfaceInit();
	/* USER CODE END Init */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */

	/* definition and creation of attitudeManager */
	osThreadDef(attitudeManager, attitudeManagerExecute, osPriorityNormal, 0,
			128);
	attitudeManagerHandle = osThreadCreate(osThread(attitudeManager), NULL);

	/* definition and creation of sensorFusion */
	osThreadDef(sensorFusion, sensorFusionExecute, osPriorityNormal, 0, 1536);
	sensorFusionHandle = osThreadCreate(osThread(sensorFusion), NULL);

	/* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument) {
	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
	/* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* attitudeManagerExecute function */
void attitudeManagerExecute(void const *argument) {

	/* USER CODE BEGIN attitudeManagerExecute */
	TickType_t xLastWakeTime;
	const TickType_t xTimeIncrement = 4;
	UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL);
	/* Infinite loop */
	for (;;) {
		// TODO: Re-add RSSI_CHECK
		xLastWakeTime = xTaskGetTickCount();

//    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		AM_interfaceExecute();
//    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		// uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}

	/* USER CODE END attitudeManagerExecute */
}

/* sensorFusionExecute function */
void sensorFusionExecute(void const *argument) {
	/* USER CODE BEGIN sensorFusionExecute */
	TickType_t xLastWakeTime;
	const TickType_t xTimeIncrement = 10; // 100Hz
	/* Inspect our own high water mark on entering the task. */
	UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL);

	/* Infinite loop */
	for (;;) {
		// Initialise the xLastWakeTime variable with the current time.
		xLastWakeTime = xTaskGetTickCount();

		// TODO: Re-add RSSI_CHECK
		// RSSI_Check();
		// HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
//    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		SensorFusionInterfaceExecute();
//    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		// uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement);
	}
}
/* USER CODE END sensorFusionExecute */
/* USER CODE END Application */
