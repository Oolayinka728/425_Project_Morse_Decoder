 /* @author Olayinka Olowookere
 */
 
 #include "TM4C123GH6PM.h"

const char* Button_to_morse(uint8_t button_status);
char Decode_Morse(const char * morse);
void MorseToString(char const *morse);