/*
 * button.h
 *
 *  Created on: 1 juin 2014
 *      Author: David
 */

#ifndef BUTTON_H_
#include "string.h"
#include "LPC17xx.h"
#define BUTTON_H_

#define NB_BUTTONS 10

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
