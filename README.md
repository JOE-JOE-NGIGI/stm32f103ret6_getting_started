I have had board lying around for quite a while and just decided it’s time I tried to explore it.

I initially struggled to find reliable documentation but recently discovered this link. It’s quite helpful if you’re trying to understand where stuff is on the board to get a basic overview.

As usual, I first wanted to be able to blink the inbuilt LED. When it worked, I wanted to document it so that I could always refer to it. Let’s get straight to what I did.

Tools
The actual board.

The STM32F103RET6 Board
2. Debugger — I used an ST-Link V2


ST Link V2 Debugger for flashing the code to the controller
3. JTAG connecter for communication between the board and debugger



The twenty PIN JTAG header connector
4. Two Mini USB cables — One to power the board and the other to power the debugger

5. An IDE — I’m using Keil MDK for this project

Blink LED Project
Assuming you have the ARM Keil MDK installed on your development PC, open it, navigate to the project, and select "create a new project."
Choose a suitable location for your project and provide a file name for the project file. I used LED_App for this project.
You then have to select the device for the target. So once that window pops up, expand the STMicroelectronics menu, expand the STM32F1 Menu, expand the STM32F103 Menu and select STM32F103RE. Then click ok.

Next, the MDK opens the ‘Manage Run-Time Environment’ window. Expand the CMSIS menu and select CORE.

Expand the Device menu, select Startup, and click OK.


‘Manage Run-Time Environment’ Window
Keil MDK automatically generates the folder structure for us. I prefer renaming my project folder to LED_Blink instead of the default ‘Target 1.’ You can do this by clicking the cursor on the extreme left of the folder name and typing your preferred label.


Project Folder Structure
Expand the Project folder menu by clicking on the + sign and update the Source Group 1 folder name to APP or whatever folder name you’d like to use for your source folder.


Project source folder
Right click on the folder we just renamed : APP and select Add new item to Group ‘APP’

In the window that pops up, select C file from the options provided, type the file name as main, and click add.


Add New Item to Group ‘APP’
Click the + sign to extend the APP folder items and double-click on main.c


our main.c file
Right-click inside the main.c file, select ‘insert #include file’ to add a device header to this source file. Select

#include "stm32f10x.h"

Adding device header to our main.c code
We need to start doing our magic now.

We aim to toggle the built-in LED on and off at a specified time interval.

We need to find out where the inbuilt LED is located. So, we head over to our documentation which was provided at the start of this tutorial.

Under the inputs and outputs section, locate the User LED. The name is LED1, and it’s connected to pin PB11.


User LED Pin number
Let’s create a quick delay immediately after our device header. Not the best way to do this but it works for a start:

// Quick and dirty delay
static void delay (unsigned int time) {
  volatile unsigned int i, j;
    for (unsigned int i = 0; i < time; i++)
        for (volatile unsigned int j = 0; j < 2000; j++);
}
Next, we create a main function:

int main (void) {

}
We start by turning on the GPIOB peripheral clock inside the main function.

int main (void) {
    // Turn on the GPIOB peripheral clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
}
Next we configure PB11 as General Purpose Output Push-pull

int main (void) {
    // Turn on the GPIOB peripheral clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    
    // Configure PB11 as General purpose output push-pull 
    GPIOB->CRH &= ~GPIO_CRH_CNF11; //clear the config bits for PB11
    GPIOB->CRH |= GPIO_CRH_MODE11_0; //set the mode for PB11 to output (max speed 10 MHz)

    
}
Then, we create a while loop to keep toggling the PB11 pin at intervals of 500 milliseconds.

#include "stm32f10x.h"                  // Device header


// Quick and dirty delay
static void delay (unsigned int time) {
  volatile unsigned int i, j;
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
At this point, we can build our code to check for errors. Either hover over the build icon near the top-left menu bar or click F7.

If you did everything correctly after building, you should not get any errors or warnings. If there are warnings or errors, please follow the compiler's recommendations to resolve them.


Happy no errors, Yaay!
It's time to flash our blinky app to the board. Connect the first mini USB to the debugger, then connect the other mini USB to the board, and use the JTAG connector to link the board to the debugger.

Finally, connect the two USB cables to a PC to power the debugger and the board.


Simple set-up
To configure the debugger, click on the options for target button at the top left of the image below.


Navigate to the Debug menu, select Use on the right of the debug menu, and select ST-Link Debugger from the drop-down menu.


Lastly, click ok.

Power on the board using the built-in blue switch. Finally, flash the code to the board (target).


Flashing the code

Powering the Board

Reset the board after successfully flashing the code
Vuala!!!

We have our in-built LED blinking.

Feel free to leave your comments for suggestions or anything really!

Cheers.

References:

https://stm32-base.org/boards/STM32F103RET6-Generic-Board.html
https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

Here is the link to the medium article for this project:
https://medium.com/@jngigiw/stm32f103ret6-getting-started-blink-internal-led-using-keil-mdk-7a1970972f37