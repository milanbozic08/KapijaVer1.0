/*

 * M590.h

 *

 * Created: 27/10/2018 14:41:49

 *  Author: Bozic

 */ 





#ifndef M590_H_

#define M590_H_



#include "UartAVR.h"

#include <string.h>

#include <stdbool.h>

#include "delay.h"



#define sms_end 0x1A

#define sim_reset 4 //D4

#define  simOff  PORTD&=~(1<<4)

#define  simOn  PORTD|=(1<<4)





bool SIM_ON();

void SIM_OFF();





void SIM_Inic();

void SIM_SendSms(char *Message,char *Number);

bool SIM_ReciveSms();

void SIM_delate_message();

bool SIM_Call_check();

void SIM_Hold_call();









#endif /* M590_H_ */