/**
 * @file main.c
 * @author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 * @version 1.0
 * @date 19 June 2014
 * @brief Receive all datas from UART (XBee device) and send them
 * @brief on the CAN bus to the Marklin station to control the trains
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "uart.h"
#include "BusCan.h"
#include "ControlTrain.h"
#include <cr_section_macros.h>
#include "string.h"
#include "stdbool.h"
#include "SendUARTFormat.h"
#endif

/**
 * String to integer
 * @param str String to be converted to a integer
 * @return The value of the string converted
 */
void CAN_IRQHandler(){
	str_bus str;
	Read_BusCan(&str);
	LPC_CAN1->CMR = 1 << 2;  //receipt interrupt
	switch(str.id_Bus)
	{
	case 0x1 :
	case 0x0 :		// Stop and go (response or global command)
		if(str.data[4] == 1)
			uart3_send(START_TRAIN, 9); // Send data on uart
		else if(str.data[4] == 0)
			uart3_send(STOP_TRAIN, 9); // Send data on uart
		break;
	case 0x9 :
	case 0x8 :  	// Speed (response or global command)
		send_speed(str.data[2] << 8 | str.data[3], str.data[4] << 8 | str.data[5]);
		break;

	case 0xB :
	case 0xA:		// Direction (response or global command)
		if(str.data[4] == 2)
			send_direction(str.data[2] << 8 | str.data[3], 0);
		else
			send_direction(str.data[2] << 8 | str.data[3], 1);
		break;

	case 0xD :
	case 0xC :		// Lights (response or global command)
		send_lights(str.data[2] << 8 | str.data[3], str.data[5]);
	break;
	}
}

/**
 * String to integer
 * @param str String to be converted to a integer
 * @return The value of the string converted
 */
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

/**
 * Receive all frame from UART (XBee) and process them to send
 * to the Marklin station with the CAN device.
 */
int main(void) {

	/* Structure to contain CAN configuration (read and write)*/
	str_bus str;

	/* Bus CAN configuration */
	Init_BusCan();
	
	/* UART 3 configured with 9600 to receive datas from XBee */
	uart3_init(9600);

	/* Length of the string */
	uint32_t len = 0;
	/* String read from UART */
	char data_read[11];

	char ch;
	bool trame_ready = false;
	while(1)
	{
		/* Read if one char is availible, if yes just add it to the string.
		 * If the string contain a end of string (0) this mean a end of fram
		 */
		if(uart3_read_one_char(&ch))
		{
			data_read[len++] = ch;
			if(ch == 0)
				trame_ready = true;
		}

		/* When a frame if ready to be read (ready when a '0' is contained in the string) */
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
				/* Turn the lights on or off */
				else if(data_read[0] == 'L' && data_read[3] == 'L')
				{
					char tmp_char[4];

					tmp_char[0] = data_read[1];
					tmp_char[1] = data_read[2];
					tmp_char[2] = 0;
					int n_train = atoi(tmp_char);
					TurnLight(&str, n_train, data_read[4]-'0');
					Write_BusCan(&str);
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
