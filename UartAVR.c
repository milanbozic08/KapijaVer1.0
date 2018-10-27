#include "UartAVR.h"

volatile char Resive[100];
volatile bool StigliPodaci=false,MozeZavrsetak=false;
volatile int i=0;

void Uart_inic()
{
	UBRRH =(MYUBRR)>>8;
	UBRRL = MYUBRR;
	
	UCSRB |= (1 << RXEN) | (1 << TXEN);      // Enable receiver and transmitter
	UCSRB |= (1 << RXCIE);                   // Enable the receiver interrupt
	UCSRC |= (1 << URSEL) |(1 << UCSZ1) | (1 << UCSZ0);    // Set frame: 8data, 1 stp
	UCSRA= 0x00;                 // Clear the UASRT status register
	
	for(int k=0;k<100;k++)
	{
		Resive[k]='\0';
	}
	
	 // set up timer with prescaler = 8
	 TCCR1B |= (1 << CS11);  // okida na 1uS
	 
	 // initialize counter
	 TCNT1 =  0;
	 
	 // enable overflow interrupt
	 TIMSK |= (1 << TOIE1);
	  
}

void uart_send_string(char *Str)
{
	int x=strlen(Str),n=0;
	for(n=0;n<x;n++)
	{
		while ( !(UCSRA & (1 << UDRE)) );   // Wait until buffer is empty

		UDR = *Str;                     // Send the data to the TX buffer
		Str++;
	}
}
bool uart_full()
{
	return StigliPodaci;
}
void uart_clear()
{
	int b=0;
	for(b=0;b<100;b++)
	{
		Resive[b]='\0';
	}
	StigliPodaci=false;
	MozeZavrsetak=false;
	i=0;
}
ISR (USART_RXC_vect)
{
	StigliPodaci=false;
	
	Resive[i]=UDR;
	i++;
	
	if(i>99) i=99;
	
	MozeZavrsetak=true;
	TCNT1 =  0;	
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 =  0;
	
	if(MozeZavrsetak==true && StigliPodaci==false)
	{
		Resive[i]='\0';
		MozeZavrsetak=false;
		StigliPodaci=true;
		i=0;
	}
	
}