/*
 * button.c
 *
 *  Created on: 1 juin 2014
 *      Author: David
 */

#include "button.h"

button_t buttons[NB_BUTTONS];
int nb_buttons_available = -1;

/**
*@brief Permit to test if a button is present where the pressure occurred
*@param x Value of x where the pressure occurred
*@param y Value of y where the pressure occurred
*/
char* IsClickOnAButton(uint16_t x, uint16_t y)
{
	int i;
	for (i = 0; i <= nb_buttons_available; i++) {
		if((buttons[i].x_start < x) && (buttons[i].x_stop > x) &&
				(buttons[i].y_start < y) && (buttons[i].y_stop > y))
			return buttons[i].name;
	}
	return 0; // No button found
}

/**
*@brief Add a new button to the list
*@param button_name String that contain button name
*@param x_start Where the button start on X
*@param x_stop Where the button start on X
*@param y_start Where the button start on Y
*@param y_stop Where the button stop on Y
*/
void AddButton(char* button_name, uint16_t x_start,uint16_t x_stop, uint16_t y_start, uint16_t y_stop)
{
	nb_buttons_available++;
	strcpy(buttons[nb_buttons_available].name, button_name);
	buttons[nb_buttons_available].x_start = x_start;
	buttons[nb_buttons_available].x_stop = x_stop;
	buttons[nb_buttons_available].y_start = y_start;
	buttons[nb_buttons_available].y_stop = y_stop;
}
