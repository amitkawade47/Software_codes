#include <avr/io.h>
#include<util/delay.h>
#include <stdio.h>
#include "uart.h"

#define NO_OF_RELAY 8
volatile unsigned char deviceOldStatus[NO_OF_RELAY], deviceNewStatus[NO_OF_RELAY];
/**************************** PIN AND PORT VARIABLES *****************************/

volatile unsigned char* inputPORT[NO_OF_RELAY] ={&PIND,&PIND,&PIND,&PIND,&PINB,&PINB,&PINC,&PINC};
const uint8_t inputPin[NO_OF_RELAY]={2,5,7,1,2,4,1,3};//{PD2,PD5,PD7,PB1,PB2,PB4,PC1,PC3};

volatile unsigned char* outputPORT[10]={&PORTD,&PORTD,&PORTD,&PORTB,&PORTB,&PORTB,&PORTC,&PORTC,&PORTC,&PORTC};
const uint8_t outputPin[8]={3,4,6,0,3,5,0,2,4,5};//{PD3,PD4,PD6,PB0,PB3,PB5,PC0,PC2,PC4,PC5};
//-------------------------{0,1,2,3,4,5,6,7,8,9}

/**********************************************************************************/

/********************************* READ PIN FUNCTION ************************************/

unsigned char readPin(unsigned char portPin)
{

	return (*inputPORT[portPin] & (1<<inputPin[portPin]))?1:0;
}

/************************************************************************************/

/************************** RELAY DRIVE FUNCTION ***********************************/

void makeRelayDrive(unsigned char drivePort,unsigned char val)
{
	drivePort=drivePort-48;
  	if(val=='1')
  	{	
		*outputPORT[drivePort] |= 1<<outputPin[drivePort];
	}
	else if (val=='0')
	{
		*outputPORT[drivePort]  &= ~(1<<outputPin[drivePort]);
	}
}

/**********************************************************************************/

/*************************** RELAY DRIVE CALL ******************************************/
void setval(char* add)
{
	if( (*add=='#')&&(*(add+2)=='@'))
	{
		makeRelayDrive(*(add+3), *(add+1));
	}

}
/***************************************************************************************/

/******************************* MAIN FUNCTIOn ****************************************/

int main(void) 
{    
	DDRD = 0b01011000; 				//Initialise pins as output and input for PORTD
	DDRB = 0b00101001; 				//Initialise pins as output and input for PORTB
	DDRC = 0b00110101; 				//Initialise pins as output and input for PORTC
	uart_init();					//UART Intialisation
    stdout = &uart_output;
    stdin  = &uart_input;
   
    unsigned char input, c=0;   	// temperory variable for storing serial data
	unsigned char* word;			// pointer variable to store incoming serial command
	word = (char*)malloc(50*sizeof(char)); //allocating memory for pointer variable
	unsigned int pinCounter[NO_OF_RELAY];	

    while(1) 
	{
    	input = getchar(); 		
		*word = input;
		if(*word=='$')				//Checking '$' in serial data 
		{
			//printf("%c\n",*(word-4));
			setval(word-4);
			word = word-4;
			c=c-4;
		}
		word++;
		c++;
		if(c>49)
		{
			word = word -50;
			c=0;
		}

		
  		for(int pin=0;pin<NO_OF_RELAY;pin++)
		{
			printf("reading pin %c\n",pin);
    		if(readPin(pin)==0)	//checks if pin becomes 0
			{ 
          		pinCounter[pin] += 1 ;		//if yes increment respective pin counter 
      		}
  		}

		for(int pin=0;pin<NO_OF_RELAY;pin++)
		{
			printf("Checking status of pin %d\n",pin);
	     	if(deviceNewStatus[pin] != deviceOldStatus[pin])
			{
				printf("status changed of pin %d\n",pin); 
		        printf("#%d@%d$",deviceNewStatus[pin]?1:0,pin);
		        deviceOldStatus[pin] = deviceNewStatus[pin] ;
	    	}
  		}



	}   
    return 0;
}
/*************************************************************************************/
