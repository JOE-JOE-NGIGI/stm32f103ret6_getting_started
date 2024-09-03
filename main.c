#include "stm32f10x.h"                  // Device header

// Quick and dirty delay
static void delay (unsigned int time) {
		//volatile unsigned int i, j;
		for (unsigned int i = 0; i < time; i++)
        for (volatile unsigned int j = 0; j < 2000; j++);
}

int main (void) {
    // Turn on the GPIOB peripheral clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Configure PB11 as General purpose output push-pull 
    GPIOB->CRH &= ~GPIO_CRH_CNF11; //clear the config bits for PB11
    GPIOB->CRH |= GPIO_CRH_MODE11_0; //set the mode for PB11 to output (max speed 10 MHz)

    while (1) {
        // Reset the state of pin 11 to output low
        GPIOB->BSRR = GPIO_BSRR_BR11;

        delay(500);

        // Set the state of pin 11 to output high
        GPIOB->BSRR = GPIO_BSRR_BS11;

        delay(500);
    }

    
}
