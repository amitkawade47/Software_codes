

#include <avr/io.h>
#include <util/delay.h>

//#include "uart.h"
//#include "config.h"
  #define F_CPU 16000000UL
  #define BAUD 9600l
  #define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden

//***********************Funktionen**********************************
void uputc(unsigned char c){		//zeichen senden

	loop_until_bit_is_set(UCSR0A,UDRE0);	// warten bis puffer frei ist
	UDR0=c;								// zeichen schreiben
}	

//*******************************************************************
void uputs (unsigned char *s){		//string senden
	
  while(*s) uputc(*s++);				//sendet zeichenkette, bis ende.. '\0'    
  
}

#if (!1)

// *******************************************************************
unsigned char ugetc(void){			//zeichen holen

  while (!(UCSR0A & (1<<RXC))) {;}	// warten bis Zeichen verfuegbar
        
  return UDR0;  		                // Zeichen aus UDR an Aufrufer zurueckgeben
}


// *******************************************************************
void ugets(char* Buffer, unsigned char MaxLen){	// zeichenkette holen
  unsigned char NextChar;
  unsigned char StringLen = 0;
 
  NextChar = ugetc();         		// Warte auf und empfange das nächste Zeichen  
                                
  while( NextChar != '\n' && StringLen < MaxLen - 1 ) {		//string ende oder puffer voll
    *Buffer++ = NextChar;
    StringLen++;
    NextChar = ugetc();
  }
   
  *Buffer = '\0';					//string abschluss
}
#endif


//*******************************************************************
void uinit (void){					//init usart Tx, 8n1 ,UDRE interupt enable

  UCSR0C |= (3<<UCSZ00);    		// URSEL = 1 dann wird UCSRC benutzt sonst UBRRH ; UCSZ0=data register- 8bit; USBS stop bit 1 	
  //Baudrate (high und low byte)
  UBRR0H = (unsigned char)(UBRR_VAL>>8);
  UBRR0L = (unsigned char)UBRR_VAL;
  UCSR0B |= (1<<TXEN0)|(1<<RXEN0);  	// UART TX,RX einschalten,	data register empty interrupt enable,
}
/*
char* str_int(int data)
{
	unsigned char* intToString = " ";
	itoa (data,intToString,10);
	return intToString;
}



char* str_uint8(uint8_t data)
{
	char* intToString = " ";
	itoa (data,intToString,10);
	return intToString;
}

char* str_uint16(uint16_t data)
{
	char* intToString = " ";
	itoa (data,intToString,10);
	return intToString;
}

char* str_float(float data,uint8_t totalDigit, uint8_t decimalNumber)
{
	
	char floatString[6] = "      ";    
	dtostrf(data,totalDigit,decimalNumber,floatString);
	return floatString;
}	
*/
int main()
{
	uinit();
//	_delay_ms(100);
	while(1)
	{
		uputs((unsigned char*)"\nLCDCS\n");
		_delay_ms(1000);
	}
	return 1;
}
