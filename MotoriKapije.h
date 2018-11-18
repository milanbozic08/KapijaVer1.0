/*

 * MotoriKapije.h

 *

 * Created: 27/09/2018 11:05:23

 *  Author: Bozic

 */ 

#include "delay.h"
#include <stdint.h>



#define M1_ON1 PORTD |=(1<<7)

#define M1_ON2 PORTC |=(1<<0)

#define M1_OFF1 PORTD &=~(1<<7)

#define M1_OFF2 PORTC &=~(1<<0)



#define M2_ON1 PORTD |=(1<<5)

#define M2_ON2 PORTD |=(1<<6)

#define M2_OFF1 PORTD &=~(1<<5)

#define M2_OFF2 PORTD &=~(1<<6)



#ifndef MOTORIKAPIJE_H_

#define MOTORIKAPIJE_H_



//extern bool TrenutnoStanje;



enum Kapija {Otvoreno,Zatvoreno};

	

extern enum Kapija Kapija1;





void OtvoriLevo()

{

	M1_ON1;

	M1_OFF2;

}

void OtvoriDesno()

{

	M2_ON1;

	M2_OFF2;

}

void ZatvoriLevo()

{

	M1_OFF1;

	M1_ON2;

}

void ZatvoriDesno()

{

	M2_OFF1;

	M2_ON2;

}



void OtvoriKapiju()

{

	if(Kapija1==Zatvoreno)

	{

		OtvoriLevo();
		_delay_ms(100);

		OtvoriDesno();

		Kapija1=Otvoreno;

		_delay_ms(500);

	}	

}

void ZatvoriKapiju()

{

	if(Kapija1==Otvoreno)

	{

		ZatvoriLevo();
		_delay_ms(100);

		ZatvoriDesno();

		Kapija1=Zatvoreno;

		_delay_ms(500);

	}

}



int ADCsingleREAD(uint8_t adctouse) //adctouse koji pin treba da se obradi

{

	int ADCval;



	ADMUX = adctouse;         // use #5 ADC

	ADMUX |= (1 << REFS0);    // use AVcc as the reference

	ADMUX &= ~(1 << ADLAR);   // clear for 10 bit resolution

	

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // 128 prescale brzina konverzije

	ADCSRA |= (1 << ADEN);    // Enable the ADC



	ADCSRA |= (1 << ADSC);    // Start the ADC conversion



	while(ADCSRA & (1 << ADSC));      // Thanks T, this line waits for the ADC to finish





	ADCval = ADCL;

	ADCval = (ADCH << 8) + ADCval;    // ADCH is read so ADC can be updated again



	return ADCval;

}





#endif /* MOTORIKAPIJE_H_ */