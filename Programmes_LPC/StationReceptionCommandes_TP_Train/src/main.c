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
#include "stdbool.h"
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

	Init_BusCan();
	
	uart3_init(9600);

	uint32_t len = 0;
	char data_read[11];

	char ch;
	bool trame_ready = false;
	while(1)
	{
		/* Test UART */
		if(uart3_read_one_char(&ch))
		{
			data_read[len++] = ch;
			if(ch == 0)
				trame_ready = true;
		}

		if(trame_ready)
		{
			switch(len)
			{
			case 6:
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
				/* Power ON the circuit */
				if(!strcmp(data_read, "STATRAIN"))
				{
					StopGoTrain(&str,1);
					Write_BusCan(&str);
				}
				/* Power off the circuit */
				else if(!strcmp(data_read,"STOTRAIN"))
				{
					StopGoTrain(&str,0);
					Write_BusCan(&str);
				}
				/* Change speed on the specified train
				 *  LxxVxxxx ==> L = line number, V = speed   */
				else if(data_read[0] == 'L' && data_read[3] == 'V')
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
			}
			trame_ready = false;
			len = 0;
		}
	}
}
