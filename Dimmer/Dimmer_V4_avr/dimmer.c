//#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/*  https://sites.google.com/site/qeewiki/books/avr-guide/external-interrupts-on-the-atmega328  */

volatile int  dimtime;
volatile int i;
int main(void)
{
	DDRB |= (1 << DDB4);
	PORTB &= ~(1 << PB4);

    DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
    // PD2 (PCINT0 pin) is now an input

    PORTD |= (1 << PORTD2);    // turn On the Pull-up
    // PD2 is now an input with pull-up enabled



    EICRA |=  (1 << ISC01)|(1 << ISC00);    // set INT0 to trigger on rising edge logic change
    EIMSK |= (1 << INT0);     // Turns on INT0

    sei();                    // turn on interrupts
	i= 0;
	dimtime = 1;
    for(;1;)
    {
		for(i=5;i>0;i--)
		{
			dimtime = i;
			_delay_ms(10000);	
		}
		for(i=0;i<5;i++)
		{
			dimtime = i;
			_delay_ms(10000);	
		}
		
	} 
}



ISR (INT0_vect)
{
	//_delay_ms(1);
	_delay_ms(dimtime);
	PORTB |= (1 << PB4);
	_delay_ms(1);
	PORTB &= ~(1 << PB4);
	/* interrupt code here */
}



