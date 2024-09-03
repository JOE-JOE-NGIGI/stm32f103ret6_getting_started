I have had board lying around for quite a while and just decided it’s time I tried to explore it.

I initially struggled to find reliable documentation but recently discovered this link. It’s quite helpful if you’re trying to understand where stuff is on the board to get a basic overview.

As usual, I first wanted to be able to blink the inbuilt LED. When it worked, I wanted to document it so that I could always refer to it. Let’s get straight to what I did.


# Tools

1. The actual board - The STM32F103RET6 Board

2. Debugger — I used an ST-Link V2

3. JTAG connecter for communication between the board and debugger

4. Two Mini USB cables — One to power the board and the other to power the debugger

5. An IDE — I’m using Keil MDK for this project

# Blink LED Project
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

Here is the link to the full tutorial for this project:

https://medium.com/@jngigiw/stm32f103ret6-getting-started-blink-internal-led-using-keil-mdk-7a1970972f37



References:

https://stm32-base.org/boards/STM32F103RET6-Generic-Board.html
https://www.st.com/resource/en/reference_manual/rm0008-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

