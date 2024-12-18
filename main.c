/**
 * @file main.c
 *
 * @brief Main source code for the GPIO program.
 *
 * This file contains the main entry point and function definitions for the GPIO program.
 * It interfaces with the following:
 *	- EduBase Board LEDs (LED0 - LED3)
 *	- EduBase Board Push Buttons (SW2 - SW5)
 *
 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Olayinka Olowookere
 */

#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "GPIO.h"
#include "UART1.h"
#include "Morse_Code.h"
#include "Button_Morse_Code.h"
int main(void)
{
	
	//Initialize the sysTick Timer used to provide a bloacking delay function
	SysTick_Delay_Init();
	//Initialize the LEDs on the EduBase board (PortB)
	RGB_LED_Init();
	
	EduBase_Button_Init();
	
	EduBase_LEDs_Init();
	
	UART1_Init();
	
	while(1)
	{
		if (LED_Display == 0)
		{
			//Enter a word.
			char str_buffer[50];
			UART1_Output_String("Enter a Word: ");
			UART1_Input_String(str_buffer, 20);
			UART1_Output_Newline();
		
			StringToMorse(str_buffer);
			UART1_Output_Newline();
		}
		
	}
}