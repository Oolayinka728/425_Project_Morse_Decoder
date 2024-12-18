/**
 * @file UART0.h
 *
 * @brief Header file for the Morse driver.
 *
 * This file contains the function definitions for the UART0 driver.
 *

 *
 * @note Assumes that the frequency of the system clock is 50 MHz.
 *
 * @author Olayinka Olowookere
 */
 #include "TM4C123GH6PM.h"
 #include <stdio.h>
 

extern volatile int LED_Display;
const char* getMorseCode(char input);
void printMorse(char input);
void StringToMorse (char *string);
void StringToMorseLED(char *string);
void LED_For_Morse(const char *morse);
 