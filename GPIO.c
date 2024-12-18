/**
 * @file GPIO.c
 *
 * @brief Source code for the GPIO driver.
 *
 * This file contains the function definitions for the GPIO driver.
 * It interfaces with the following:
 *	- EduBase Board LEDs (LED0 - LED3)
 *	- EduBase Board Push Buttons (SW2 - SW5)
 *
 *
 * @author Olayinaka Olowookere
 */

#include "GPIO.h"
#include "TM4C123GH6PM.h"

// Constant definitions for the user LED (RGB) colors
const uint8_t RGB_LED_OFF 		= 0x00;
const uint8_t RGB_LED_RED 		= 0x02;
const uint8_t RGB_LED_BLUE 		= 0x04;
const uint8_t RGB_LED_GREEN 	= 0x08;

// Constant definitions for the EduBase board LEDs
const uint8_t EDUBASE_LED_ALL_OFF = 0x0;
const uint8_t EDUBASE_LED_ALL_ON	= 0xF;

void RGB_LED_Init(void)
{
	// Enable the clock to Port F
	SYSCTL->RCGCGPIO |= 0x20;

	// Set PF1, PF2, and PF3 as output GPIO pins
	GPIOF->DIR |= 0x0E;
	
	// Configure PF1, PF2, and PF3 to function as GPIO pins
	GPIOF->AFSEL &= ~0x0E;
	
	// Enable digital functionality for PF1, PF2, and PF3
	GPIOF->DEN |= 0x0E;
	
	// Initialize the output of the RGB LED to zero
	GPIOF->DATA &= ~0x0E;
}

void RGB_LED_Output(uint8_t led_value)
{
	// Set the output of the RGB LED
	GPIOF->DATA = (GPIOF->DATA & 0xF1) | led_value;
}

uint8_t RGB_LED_Status(void)
{
	// Assign the value of Port F to a local variable
	// and only read the values of the following bits: 3, 2, and 1
	// Then, return the local variable's value
	uint8_t RGB_LED_Status = GPIOF->DATA & 0x0E;
	return RGB_LED_Status;
}



void EduBase_LEDs_Init(void)
{
	//Enable the clock to port B
	SYSCTL->RCGCGPIO |= 0x02;
	
	//Set PB0, PB1, PB2,PB3 as output GPIO pins
	GPIOB->DIR |= 0x0C;
	
	//Configure PB0, PB1, PB2, and PB3 to function as GPIO pins
	GPIOB->AFSEL &= ~0x0C;
	
	//Enable digital functionality for Pb0, Pb1, Pb2, and Pb3
	GPIOB->DEN |= 0x0C;
	
	//Initialize the output of the Edubase LEDs to zero
	GPIOB->DATA &= ~0x0C;

}

void EduBase_LEDs_Output(uint8_t led_value)
{
	//Set the output of the LEDs
	GPIOB->DATA = (GPIOB ->DATA & 0xC0) | led_value;
}

void EduBase_Button_Init(void)
{
	//Enable the clock to Port D
	SYSCTL->RCGCGPIO |= 0x08;
	
	//Set Pd0, Pd1, Pd2, Pd3 as input GPIO pins
	GPIOD->DIR &= ~0x0F;
	
	//Configure Pd0, Pd1, Pd2,Pd3 to function as gpio pins
	GPIOD->AFSEL &= ~0x0F;
	
	// Enable digital funcgtionality for Pd0, Pd1,Pd2, Pd3
	GPIOD->DEN |= 0x0F;
}

uint8_t Get_EduBase_Button_Status(void)
	
{
	//Assign the value of Port D to a local variable
	//and only read the values of the  follwowing bits: 3,2,1 and 0
	// Then return the local variable's value
	uint8_t button_status = GPIOD->DATA & 0x0C;
	return button_status;
}


 void LED_Controller(uint8_t button_status)
{
	switch (button_status)
	{
		case 0x01:
		{
			RGB_LED_Output(RGB_LED_GREEN);
			break;
		}
		case 0x02:
		{
			RGB_LED_Output(RGB_LED_RED);
			break;
		}
		default:
		{
			RGB_LED_Output(RGB_LED_OFF);
			break;
		}
	}
}

