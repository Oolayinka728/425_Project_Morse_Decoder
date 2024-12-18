#include <stdint.h>// used for ints
#include <string.h>//Used to concatinate the morses in a buffer array
#include <stdio.h>//used to format into a character buffer array
#include "TM4C123GH6PM.h"

#include "GPIO.h"
#include "UART1.h"
#include "Morse_Code.h"

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

//Rather than measuring the time duration,
//Here we are going to set SW3 as (.) and SW4 as (_) and SW5 as space

const char* Button_to_morse(uint8_t button_status)
{
	char string [100] = "";
	char input;
	for (int i = 0; i<99; i++)//The last string is a null value.
  {
		if (button_status == 0x04)
    {
		input = '.';
	  }
	  else if (button_status == 0x02)
	  {
		  input = '-';
	  }
	  else if (button_status == 0x01)
	  {
		  input = ' ';
	  }
		  string[i] = input;
	}
	return string;
}
//Decode the given morse code
char Decode_Morse(const char * morse)
{
	 for (int i = 0; i < 26; i++) {
        if (morseTable[i].morse == morse) {
            return morseTable[i].letter; // Return the Morse code as a string
        }
    }
		return NULL;
}

//Now we want to print out the string

void MorseToString(char const *morse)
{
	char str_buffer[100];
	char morse_buffer[10];
	int morse_index = 0;
	int str_index = 0;
	int len = strlen(morse);//length of the morse value;
	for (int i = 0;i<len;i++)
	{
		//Identify each morse value
		if(morse[i] != ' ' && morse[i] !=  '\0')//If we dont have a space or the 0 at the end of a string
		{
			morse_buffer[morse_index] = morse[i];
			morse_index++;
		}
		else if(morse[i] == ' ' && (morse_index>0))//End of String
		{
			char decode_letter = Decode_Morse(morse_buffer);
			if (decode_letter != NULL)
			{
				str_buffer[str_index] = decode_letter;
				str_index++;
			}
			morse_index = 0;
		}
		if(morse[i] == ' ')
		{
			str_buffer[str_index] = ' ';
			str_index++;
		}
		
	}
	
	UART1_Output_String(str_buffer);
	UART1_Output_Newline();
}

