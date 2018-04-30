/*
 * Demonstration on how to redirect stdio to UART. 
 *
 * http://appelsiini.net/2011/simple-usart-with-avr-libc
 *
 * To compile and upload run: make clean; make; make program;
 * Connect to serial with: screen /dev/tty.usbserial-*
 *
 * Copyright 2011 Mika Tuupola
 *
 * Licensed under the MIT license:
 *   http://www.opensource.org/licenses/mit-license.php
 *
 */
 
#include <stdio.h>

#include "main.h"
#include "uart.h"

void setval(char* add){
//	printf("inFunction%p\n", add);
//	printf("%s\n",add);
	if( (*add=='#')&&(*(add+2)=='@')){
		printf("%c\n",*(add+1));// digitalWrite()
		printf("%c\n",*(add+3));
	}

}


int main(void) {    

    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
    Flags.all_flags = 0U;
    char input;
	char* word, init;
	init = word = (char*)calloc(100, sizeof(char));

    while(1) {
       // puts("Hello world!");
        input = getchar(); 
	//	printf("%p\n", word);
			
		 *word = input;
		if(*word=='$')	
		{
			printf("%s\n",word-4);
			setval(word-4);
			printf("before%p\n", word);
	//		printf("%p\n", init);
			word = init;
	//		printf("after%p\n", word);
		}
		word++;

	 }
       
    return 0;
}
