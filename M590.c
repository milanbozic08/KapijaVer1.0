#include "M590.h"

bool SIM_ON()
{
	bool state_sim=false;
	_delay_ms(1000);
	
	simOn;
	_delay_ms(1500);
	uart_clear();
	while(!state_sim)
	{
		if(uart_full())
		{
			if(strcmp("\r\n+PBREADY\r\n",Resive)==0)
			state_sim=true;
		}
	}
	return true;
}

void SIM_OFF()
{
	simOff;
}

void SIM_SendSms(char *Message,char *Number)
{
	
	char num[50]="AT+CMGS=\"";
	strcat(num,Number);
	strcat(num,"\"\r");
	
	
	uart_send_string("AT+CSCS=\"GSM\"\r");
	_delay_ms(2000);
	uart_send_string("AT+CMGF=1\r");
	_delay_ms(2000);
	
	uart_send_string(num);
	_delay_ms(1000);
	uart_send_string(Message);
	_delay_ms(20);
	UDR=sms_end;
	_delay_ms(1000);
}

void SIM_delate_message()
{
	_delay_ms(500);
	uart_send_string("AT+CMGD=0\r");
	_delay_ms(500);
	uart_send_string("AT+CMGD=1\r");
	_delay_ms(500);
	uart_send_string("AT+CMGD=2\r");
	_delay_ms(500);
	uart_send_string("AT+CMGD=3\r");
	_delay_ms(500);
	uart_send_string("AT+CMGD=4\r");
	_delay_ms(500);
}

void SIM_Inic()
{
	Uart_inic();
	sei();
	
	simOff;
	_delay_ms(500);
	DDRD|=(1<<4);
	_delay_ms(500);
	SIM_ON();
	
}