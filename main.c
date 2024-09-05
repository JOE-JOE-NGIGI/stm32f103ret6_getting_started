//=====Includes========//
#include "stm32f10x.h"                  // Device header

//====Function prototypes====//
static void SysTick_Init(void); //Declare SysTick_Init as static
static void delay(uint32_t ms); //Declare delay function as static

//milliseconds counter declared as static coz it's only used in this file
static volatile uint32_t msTicks = 0; 

//SysTick interrupt handler, to be called every millisecond
void SysTick_Handler(void) {
	msTicks++; //increment the millisecond counter
}

//initialize SysTick to generate 1ms interrupts
void SysTick_Init(void) {
	//load SysTick to interrupt every 1ms
	if (SysTick_Config(SystemCoreClock / 1000)) {
		// Handle the error (if the return value is 1, it indicates an error)
		while (1);
		}
}

//Delay function using SysTick
void delay(uint32_t ms) {
	uint32_t startTicks = msTicks; //store the current millisecond count
	while ((msTicks - startTicks) < ms); //wait until enough milliseconds have passed
}

int main (void) {
    // Turn on the GPIOB peripheral clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Configure PB11 as General purpose output push-pull 
    GPIOB->CRH &= ~GPIO_CRH_CNF11; //clear the config bits for PB11
    GPIOB->CRH |= GPIO_CRH_MODE11_0; //set the mode for PB11 to output (max speed 10 MHz)
	
		//initialize SysTick for 1ms timing
		SysTick_Init();

    while (1) {
        // Reset the state of pin 11 to output low
        GPIOB->BSRR = GPIO_BSRR_BR11;

        delay(1000);

        // Set the state of pin 11 to output high
        GPIOB->BSRR = GPIO_BSRR_BS11;

        delay(1000);
    }

    
}
