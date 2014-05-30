/**
 *@file main.c
 *@author Swagteam
 *@version 1.0
 *@date 29 avril 2014
 *@brief content constants and header of functions used on BusCan.h
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "uart.h"
#include "BusCan.h"
#include "ControlTrain.h"
#include <cr_section_macros.h>
#endif


int main(void) {
	str_bus str;
	int speed,NoTrain;

	Init_BusCan();
	NoTrain = 44;
	speed = 400;

	StopGoTrain(&str,1);
	Write_BusCan(&str);

	ChangeDirection(&str,NoTrain,FORWARD_TRAIN);
	Write_BusCan(&str);

	ChangeSpeed(&str,NoTrain,speed);
	Write_BusCan(&str);
	
	uart3_init(9600);
	char data_in[10];
	uint32_t len;
	char data_send[10] = "LXXSXVXXXX";
	char ch[10];
	while(1)
	{
		/* Test UART */
		len = uart3_read(&ch, 10);
	}
}
