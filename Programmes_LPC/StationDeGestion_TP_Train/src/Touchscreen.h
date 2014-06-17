/*
 * Touchscreen.h
 *
 *  Created on: 15 mars 2014
 *      Author: David
 */

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

#include "LPC17xx.h"
#include <cr_section_macros.h>
#include "SPI.h"
#include "Ecran.h"

#define IRQ_Touchscreen 0  	// P2.0
#define ExtLab2_IRQ 10 		// P2.10
#define CS_touchscreen 8		// P0.8

void Init_touchscreen();
uint16_t Read_y_12bits();
uint16_t Read_x_12bits();
void Read_x_and_y_12bits(uint16_t* x, uint16_t* y);

#endif /* TOUCHSCREEN_H_ */
