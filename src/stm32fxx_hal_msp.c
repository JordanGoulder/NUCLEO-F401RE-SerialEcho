/**
  ******************************************************************************
  * @file   stm32fxx_hal_msp.c
  * @author Jordan Goulder
  * @brief  Implements MCU Support Package functions that perform low level
  *         peripheral initialization. This functions are called by the HAL.
  ******************************************************************************
*/

#include "stm32f4xx_hal.h"

void HAL_UART_MspInit(UART_HandleTypeDef *hUart)
{
    // USART2 pins are on PA2 and PA3
    // Enable GPIO Port A clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Enable USART2 clock
    __HAL_RCC_USART2_CLK_ENABLE();

    // Structure used to initialize GPIO pins
    GPIO_InitTypeDef gpioInit;

    // Configure GPIO TX pin
    gpioInit.Pin = GPIO_PIN_2;
    gpioInit.Mode =  GPIO_MODE_AF_PP;
    gpioInit.Alternate = GPIO_AF7_USART2;
    gpioInit.Pull = GPIO_PULLUP;
    gpioInit.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIOA, &gpioInit);

    // Configure GPIO RX pin
    gpioInit.Pin = GPIO_PIN_3;
    gpioInit.Mode =  GPIO_MODE_AF_PP;
    gpioInit.Alternate = GPIO_AF7_USART2;
    gpioInit.Pull = GPIO_PULLUP;
    gpioInit.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIOA, &gpioInit);
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    // Reset USART2
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();

    // Put GPIO pins back to default state
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
}
