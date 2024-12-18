/**
 * @file Morse_Code.c
 *
 * @brief Morse Code source code for the UART

 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Olayinka Olowookere
*/


#include <stdint.h>// used for ints
#include <string.h>//Used to concatinate the morses in a buffer array
#include <stdio.h>//used to format into a character buffer array
#include "TM4C123GH6PM.h"

#include "UART1.h"
#include "SysTick_Delay.h"
#include "GPIO.h"

extern volatile int LED_Display = 0;//We want to play out the entire sequence before prompting another input

typedef struct{//use to map each of the morse code with their alphabetical values
	char letter;
	const char *morse;
	
} MorseCode;


MorseCode morseTable[] = { {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
    {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
    {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
    {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
    {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."}
};
//Now, for any letter input, give us the morse code.
 const char* getMorseCode(char input)//Gives us the morser code.
{
		 for (int i = 0; i < 26; i++) {
        if (morseTable[i].letter == input) {
            return morseTable[i].morse; // Return the Morse code as a string
        }
    }
		return NULL;
	
}

void printMorse(char input)//Debug. testing the getMorseCode function
{
	char buffer[50];
	//Call the get_morse code and store it
	char *morseCode = getMorseCode(input);
	if(morseCode != NULL)
	{
		sprintf (buffer, "The Morse code for %c is: %s\n", input, morseCode);
		UART1_Output_String(buffer);
		UART1_Output_Newline();
	}else{
		sprintf(buffer, "Error");
		UART1_Output_String(buffer);
		UART1_Output_Newline();
	}
	
}


//Now for the LED Outputs
//We are going to use the RGB LEDs
//LED 0 for dot(.)
//LED 1 for (_)
//Same function as before, only now we are outputting LEd values instead of the morse code itself
void LED_For_Morse(const char *morse)
{
	LED_Display = 1;//Start the sequece
	int len = strlen(morse);
	for(int i = 0; i < len; i++)
	{
		if (morse[i] == '.')
		{
			RGB_LED_Output(RGB_LED_RED);
			SysTick_Delay1ms(250);
			RGB_LED_Output(RGB_LED_OFF);
			SysTick_Delay1ms(250);
		}
		else if (morse[i] == '-')
		{
			RGB_LED_Output(RGB_LED_RED);
			SysTick_Delay1ms(750);
			RGB_LED_Output(RGB_LED_OFF);
			SysTick_Delay1ms(250);
		}
		else if (morse[i] == ' ')
		{
			SysTick_Delay1ms(750);
		}	
	}
	LED_Display  = 0;//Stop the Sequence
}

 void StringToMorse (char *string)//Now we are going to loop thru the  string
//and find the corresponding morse code for it.
{
	char buffer[100] = "";//Buffer to hold the converted strings.
	int len = strlen(string);
	
	for(int i= 0; i < len; i++)
	{
		char letter = string[i];//here we iterate thru the string arry and assign each of them to a letter
		
		const char *morseCode = getMorseCode(letter);
		if (morseCode != NULL)
		{
			//add the converterd string to the morsecode buffer (Concatination0
			strcat(buffer, morseCode);
			//we might need to space the concatinatino later on
			strcat(buffer, " ");

			
		}
		else{
			strcat(buffer, " ");//concatination function
			
		}
		
	}
	UART1_Output_String(buffer);
	UART1_Output_Newline();
	
	//SysTick_Delay1ms(100);
	
	LED_For_Morse(buffer);
}




