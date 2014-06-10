/*
 * ControlTrain.c
 *
 *  Created on: 4 juin 2014
 *      Author: David
 */
#include "ControlTrain.h"

void send_speed(uint8_t n_train, uint16_t speed_train)
{
	char data_send[10] = "LxxVxxxx";
	data_send[1] = n_train / 10 + '0';
	data_send[2] = n_train % 10 + '0';
	data_send[4] = speed_train / 1000 + '0';
	data_send[5] = (speed_train % 1000) / 100 + '0';
	data_send[6] = (speed_train % 100) / 10 + '0';
	data_send[7] = speed_train % 10 + '0';

	uart3_send(data_send, 9); // Send data on uart
}

void send_direction(uint8_t n_train, bool direction)
{
	char data_send[10] = "LxxSx";
	data_send[1] = n_train / 10 + '0';
	data_send[2] = n_train % 10 + '0';
	data_send[4] = direction + '0';

	uart3_send(data_send, 6); // Send data on uart
}

void send_lights(uint8_t n_train, bool state)
{
	char data_send[10] = "LxxLx";
	data_send[1] = n_train / 10 + '0';
	data_send[2] = n_train % 10 + '0';
	data_send[4] = state + '0';

	uart3_send(data_send, 6); // Send data on uart
}
