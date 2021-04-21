#include "bluetooth.h"

volatile char rx[2];
volatile char command[2] = "nn";

void BT_start()
{
	HAL_UART_Receive_IT(&huart2, &rx, 2);
}


void BT_send_message(uint8_t *data)
{
	HAL_UART_Transmit(&huart2, data, strlen(data), 100);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	strncpy(command, rx, 2);
	HAL_UART_Receive_IT(&huart2, &rx, 2);
}
