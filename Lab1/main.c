
/*
This code will cause a TekBot connected to the AVR board to
move forward and when it touches an obstacle, it will reverse
and turn away from the obstacle and resume forward motion.

PORT MAP
Port B, Pin 5 -> Output -> Right Motor Enable
Port B, Pin 4 -> Output -> Right Motor Direction
Port B, Pin 6 -> Output -> Left Motor Enable
Port B, Pin 7 -> Output -> Left Motor Direction
Port D, Pin 5 -> Input -> Left Whisker
Port D, Pin 4 -> Input -> Right Whisker
*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
	// Initialize ports
	DDRB = 0b11110000;
	PORTB = 0b11110000;
	
	DDRD = 0b11001111;
	PORTD = 0b00110000;
		
	while (1) // loop forever
	{
		// Drive forward
		PORTB = 0b10010000;
		// Sets mpr as input
		uint8_t mpr = PIND & 0b00110000;
		// Checks if either whisker is hit
		if(mpr == 0b00010000 || mpr == 0b00100000){
			
			// Handling for switch debouncing (not sure if necessary)
			// Delays by 50 ms then checks the input, as I had a problem with the behavior for both whiskers hit. It would randomly choose between left or right
			_delay_ms(50);
			mpr = PIND & 0b00110000;
			// Both whiskers are hit
			if((mpr & 0b00110000) == 0b0000000){
				PORTB = 0b00000000;
				_delay_ms(1000);
				
				PORTB = 0b00010000;
				_delay_ms(1000);
			}
			// Right whisker is hit
			else if(mpr == 0b00100000){
				PORTB = 0b00000000;
				_delay_ms(1000);	
			
				PORTB = 0b00010000;
				_delay_ms(1000);		
			}
			// Left whisker is hit
			else if(mpr == 0b00010000){
				PORTB = 0b00000000;
				_delay_ms(1000);
			
				PORTB = 0b10000000;
				_delay_ms(1000);
			}
		}
		// Continue forward
		PORTB = 0b10010000;
	}
}