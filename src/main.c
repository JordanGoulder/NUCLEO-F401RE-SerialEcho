/**
  ******************************************************************************
  * @file   main.c
  * @author Jordan Goulder
  * @brief  Reads characters from the serial port and writes back all characters
  *         as upper case.
  ******************************************************************************
*/

#include <ctype.h>
#include <string.h>
#include "stm32f4xx.h"
#include "stm32f4xx_nucleo.h"

void error_handler();

int main(void)
{
    // Initialize the Hardware Abstraction Library
    HAL_Init();

    // Initialize LED2, it remain solid unless there is an error
    // If there is an error, LED2 will be blinking
    BSP_LED_Init(LED2);
    BSP_LED_On(LED2);

    // Configure the USART settings
    UART_HandleTypeDef hUart;
    memset(&hUart, 0, sizeof(hUart));

    hUart.Instance             = USART2;
    hUart.Init.BaudRate        = 9600;
    hUart.Init.WordLength      = UART_WORDLENGTH_8B;
    hUart.Init.Parity          = UART_PARITY_NONE;
    hUart.Init.StopBits        = UART_STOPBITS_1;
    hUart.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
    hUart.Init.Mode            = UART_MODE_TX_RX;
    hUart.Init.OverSampling    = UART_OVERSAMPLING_8;

    // Initialize the USART
    if (HAL_UART_Init(&hUart) != HAL_OK)
    {
        error_handler();
    }

    // Loop forever converting incoming characters to upper case and sending
    // the back
    for(;;)
    {
        unsigned char c;

        // Read a character from the USART
        HAL_UART_Receive(&hUart, &c, 1, HAL_MAX_DELAY);

        // Convert the character to upper case
        c = toupper(c);

        // Write the upper case character to the UART
        HAL_UART_Transmit(&hUart, &c, 1, HAL_MAX_DELAY);
    }
}

void error_handler()
{
    // loop forever flashing LED2
    while(1)
    {
        BSP_LED_Toggle(LED2);
        HAL_Delay(500);
    }
}
