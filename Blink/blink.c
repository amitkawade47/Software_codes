#include <avr/io.h>
#include <util/delay.h>



int main()
{
	DDRB = 1<<PB5;
	PORTB = 0x00;

	while(1)
	{
		PORTB = 1<<PB5;
		_delay_ms(1000);
		PORTB = 0<<PB5;
		_delay_ms(1000);
	}
}
