#include "bluetooth.h"

volatile char rx[2];
volatile char command[2] = "nn";
volatile uint8_t command_flag = 0;

void BT_start()
{
	HAL_UART_Receive_IT(&huart2, &rx, 2);
}

void BT_stop()
{
	HAL_UART_AbortReceive(&huart2);
}


void BT_send_message(uint8_t *data)
{
	HAL_UART_Transmit(&huart2, data, strlen(data), 100);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	strncpy(command, rx, 2);
	HAL_UART_Receive_IT(&huart2, &rx, 2);
	command_flag = 1;
}
