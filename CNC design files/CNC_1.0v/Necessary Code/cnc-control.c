/*
 * GccApplication3.c
 *
 * Created: 2015-04-01 6:13:58 AM
 *  Author: Bangladesh
 */ 


#include <avr/io.h>   
#include <util/delay.h> 
#include <avr/interrupt.h>
#define led PD2 
#define led_port PORTD 
#define led_ddr DDRD 
#define F_CPU 16000000UL


int main(void)
{ 
	
	led_ddr |= (1 << 2); //enable led as an output pin   
	TCCR1B |= (1 << WGM12);  // configuring timer 1 for ctc mode
	TIMSK1 |= (1 << OCIE1A); // enable ctc interrupt
	sei(); //Enable global interrupts
	OCR1A = 15624; //Sets ctc compare value to 1hz at 1mhz AVR clock, with prescaler of 64
	TCCR1B |= ((1 << CS12) | (1<< CS10)); //setup for timer at clkio/64 (prescaler)
    while(1)
     {
		
	}
		
	 
} 
ISR(TIMER1_COMPA_vect)
{
	led_port ^= (1 << 2);
}

