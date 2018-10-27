/*
 * UartAVR.h
 *
 * Created: 27/10/2018 14:27:49
 *  Author: Bozic
 */ 


#ifndef UARTAVR_H_
#define UARTAVR_H_

#ifndef F_CPU1
#define F_CPU1 8000000
#endif

#ifndef BAUD
#define BAUD 9600
#endif

#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>

#define MYUBRR F_CPU1/16/BAUD -1

volatile extern char Resive[];

void Uart_inic();
void uart_send_string(char *);
bool uart_full();
char* uart_full_string();
void uart_clear();




#endif /* UARTAVR_H_ */