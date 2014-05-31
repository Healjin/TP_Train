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
#include "string.h"
#endif


int atoi(char *str)
{
    int res = 0; // Initialize result
    int i;
    // Iterate through all characters of input string and update result
    for (i = 0; str[i] != '\0'; ++i)
        res = res*10 + str[i] - '0';

    // return result.
    return res;
}


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

	uint32_t len;
	char data_send[11] = "LXXSXVXXXX";
	char data_read[11];
	while(1)
	{
		/* Test UART */
		len = uart3_read(data_read, 11);


		switch(len)
		{
		case 5:
			/* Change direction on the specified train
			 *  LxxSx ==> L = line number, S = direction   */
			if(data_read[0] == 'L' && data_read[3] == 'S')
			{
				char tmp_char[4];

				tmp_char[0] = data_read[1];
				tmp_char[1] = data_read[2];
				tmp_char[2] = 0;
				int n_train = atoi(tmp_char);

				if(data_read[4] == '1')
				{
					ChangeDirection(&str,n_train,FORWARD_TRAIN);
					Write_BusCan(&str);
				}
				else if(data_read[4] == '0')
				{
					ChangeDirection(&str,n_train,BACK_TRAIN);
					Write_BusCan(&str);
				}
			}
			break;
		case 9:
			/* Change speed on the specified train
			 *  LxxVxxxx ==> L = line number, V = speed   */
			if(data_read[0] == 'L' && data_read[3] == 'V')
			{
				char tmp_char[4];

				tmp_char[0] = data_read[1];
				tmp_char[1] = data_read[2];
				tmp_char[2] = 0;
				int n_train = atoi(tmp_char);

				tmp_char[0] = data_read[4];
				tmp_char[1] = data_read[5];
				tmp_char[2] = data_read[6];
				tmp_char[3] = data_read[7];
				tmp_char[4] = 0;

				int speed = atoi(tmp_char);
				ChangeSpeed(&str,n_train,speed);
				Write_BusCan(&str);
			}
			break;
		case 10:
			/* Power ON the circuit */
			if(strcmp("STATRAIN", data_read))
			{
				StopGoTrain(&str,1);
				Write_BusCan(&str);
			}
			/* Power off the circuit */
			else if(strcmp("STOTRAIN", data_read))
			{
				StopGoTrain(&str,0);
				Write_BusCan(&str);
			}
			break;
		}
	}
}
