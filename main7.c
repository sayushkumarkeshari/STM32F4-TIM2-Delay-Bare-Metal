/*Using Timers of STM32F4 for generating accurate Time Delays   */
#include "stm32f446xx.h"

void delay(uint32_t delay)
{
    TIM2->CNT = 0;

    while(TIM2->CNT < delay);
}

int main(void)
{
    RCC->AHB1ENR |= (1<<0);   // Enable GPIOA clock

    GPIOA->MODER &= ~(3<<10);
    GPIOA->MODER |=  (1<<10);    // PA5 Output

    GPIOA->OTYPER &= ~(1<<5);
    GPIOA->OSPEEDR &= ~(3<<10);

	//Turn ON clock for timer 2
    RCC->APB1ENR |= (1<<0);

    TIM2->PSC = 16000 - 1;
	//Load autore- loaded vlaue ARR value
    TIM2->ARR = 0xFFFFFFFF;   // Large auto-reload value
	//Turn on the timer counter
    TIM2->CR1 |= (1<<0);

    while(1)
    {
        GPIOA->ODR |= (1<<5);
        delay(1000);

        GPIOA->ODR &= ~(1<<5);
        delay(1000);
    }
}
	