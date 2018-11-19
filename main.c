// RADI
#define F_CPU 8000000UL

#include <avr/io.h>

#include "MotoriKapije.h"

#include "M590.h"

#include "delay.h"

//#include <avr/interrupt.h>

#include <stdbool.h>


 


volatile bool RING=false,RING_sw=false;



enum Kapija Kapija1=Otvoreno;



volatile int M1ADC=370,M2ADC=255;



ISR(INT0_vect)

{

	RING=true;

}



int main(void)

{

	_delay_ms(100);

	MCUCR = 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on falling edge// low lewel

	GICR = 1<<INT0;					// Enable INT0

	

	PORTD |= (1 << 2);

	DDRD&= ~(1<<2); //Ring

	

	M1_OFF1;

	M1_OFF2;

	M2_OFF1;

	M2_OFF2;

	DDRD|= (1<<7); //M1

	DDRC|= (1<<0); //M1

	DDRD|= (1<<6); //M2

	DDRD|= (1<<5); //M2

	

	DDRB&= ~(1<<1); // taster

	

	SIM_Inic();



	sei();

	

	_delay_ms(10000);

	

	RING=false;

	

	M1_OFF1;

	M1_OFF2;

	M2_OFF1;

	M2_OFF2;

	

	while(1)

	{

		if( (PINB & (1<<PINB1)) == 0)

		{
			uart_clear();
			
			RING =true;
			RING_sw=true;

			

			_delay_ms(50);

			while((PINB & (1<<PINB1)) == 0);

			_delay_ms(500);

		}

		

		if(ADCsingleREAD(3)>M2ADC)

		{

			M2_OFF1;

			M2_OFF2;

		}

		if(ADCsingleREAD(4)>M1ADC)

		{

			M1_OFF1;

			M1_OFF2;

		}

		

		if(RING)

		{
			if(SIM_Call_check() || RING_sw)
			{
				RING=false;
				RING_sw=false;
				SIM_Hold_call();
				

				if(Kapija1!=Otvoreno)

				{

					OtvoriKapiju();

				}

				else

				{

					ZatvoriKapiju();

				}

			}
			
			uart_clear();
			

			

		}

		

	}

	

}