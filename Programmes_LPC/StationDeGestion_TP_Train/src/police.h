/*
 * police.h
 *
 *  Created on: 14 mars 2014
 *      Author: David
 */

#ifndef POLICE_H_
#define POLICE_H_

#include "LPC17xx.h"
#include <cr_section_macros.h>
#include "Ecran.h"

#define LETTER_WIDTH 8
#define LETTER_HEIGHT 22

void Write_char(char character, uint8_t x,uint8_t y, uint8_t *color);

void Write_char_with_background(char character, uint8_t x,uint8_t y, uint8_t *color_letter, uint8_t *color_background);

#endif /* POLICE_H_ */
