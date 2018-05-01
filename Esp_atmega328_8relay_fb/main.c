#include <avr/io.h>
#include<util/delay.h>
 
#include <stdio.h>

#include "uart.h"

volatile unsigned char* inputPORT[8] ={&PIND,&PIND,&PIND,&PIND,&PINB,&PINB,&PINC,&PINC};
const uint8_t inputPin[8]={2,5,7,1,2,4,1,3};//{PD2,PD5,PD7,PB1,PB2,PB4,PC1,PC3};

volatile unsigned char* outputPORT[10]={&PORTD,&PORTD,&PORTD,&PORTB,&PORTB,&PORTB,&PORTC,&PORTC,&PORTC,&PORTC};
const uint8_t outputPin[8]={3,4,6,0,3,5,0,2,4,5};//{PD3,PD4,PD6,PB0,PB3,PB5,PC0,PC2,PC4,PC5};
//-------------------------{0,1,2,3,4,5,6,7,8,9}
unsigned char readPin(unsigned char portPin)
{
	return (*inputPORT[portPin] & (1<<inputPin[portPin]))?1:0;
}
 
void makeRelayDrive(unsigned char drivePort,unsigned char val)
{
	//printf("%c",drivePort);
//	printf("%c",val);
	drivePort=drivePort-48;
  	if(val=='1')
  	{	
		*outputPORT[drivePort] |= 1<<outputPin[drivePort];
	//	_delay_ms(1000);
	//	printf("on\n");

	}
	else if (val=='0')
	{
		*outputPORT[drivePort]  &= ~(1<<outputPin[drivePort]); 
	//	_delay_ms(1000);
	//	printf("off\n");
	}

}



void setval(char* add){
	if( (*add=='#')&&(*(add+2)=='@')){
		makeRelayDrive(*(add+3), *(add+1));
	}

}


int main(void) {    
	
	DDRD = 0b01011000; //Initialise pins as output and input
//	PORTD =0b10100111; //Making input pins pull up

	DDRB = 0b00101001; //Initialise pins as output and input
//	PORTB =0b11010110; //Making input pins pull up
	
	DDRC = 0b00110101; //Initialise pins as output and input
//	PORTC =0b11001010; //Making input pins pull up
    
	uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
   
    unsigned char input, c=0;   // temperory variable for soring serial data
	unsigned char* word;
	word = (char*)malloc(50*sizeof(char));
	
    while(1) {
       // puts("Hello world!");
        input = getchar(); 
		printf("%c", input);
			
		 *word = input;
//		printf("%c", *word);

		if(*word=='$')	
		{
			printf("%c\n",*(word-4));
			setval(word-4);
			word = word-4;
			c=c-4;
		}
		word++;
		c++;
		if(c>49){
			word = word -50;
			c=0;
		}

	 }
       
    return 0;
}
