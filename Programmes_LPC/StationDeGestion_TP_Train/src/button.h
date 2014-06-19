/**
 *@file button.h
 *@author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 *@version 1.0
 *@date 19 June 2014
 *@briefs Permit to add buttons (virtuals) and to test when we
 *@briefs press on the screen if the preassure is on a button.
 */

#ifndef BUTTON_H_
#include "string.h"
#include "LPC17xx.h"
#define BUTTON_H_

#define NB_BUTTONS 10

/* Structure used to store a button */
typedef struct {
	char name[20];
	uint16_t x_start;
	uint16_t x_stop;
	uint16_t y_start;
	uint16_t y_stop;
} button_t;

void AddButton(char* button_name, uint16_t x_start, uint16_t x_stop, uint16_t y_start, uint16_t y_stop);
char* IsClickOnAButton(uint16_t x, uint16_t y);

#endif /* BUTTON_H_ */
