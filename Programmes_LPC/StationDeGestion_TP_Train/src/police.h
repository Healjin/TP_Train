/*
*@file police.h
*@author Swagteam
*@version 1.0
*@date 11 march 2014
*@brief content constants and header of functions used on police.c
*/
#ifndef POLICE_H_
#define POLICE_H_

#include "LPC17xx.h"
#include <cr_section_macros.h>
#include "Ecran.h"
#include <math.h>


#define LETTER_WIDTH 8
#define LETTER_HEIGHT 22

void Write_char(char character, uint16_t x,uint16_t y, uint8_t *color);
void Write_string(char * string,uint8_t x,uint8_t y, uint8_t *color_character);
void Write_string_with_background(char * string,uint8_t x,uint8_t y, uint8_t *color_character,uint8_t *color_background);
void Write_char_with_background(char character, uint8_t x,uint8_t y, uint8_t *color_letter, uint8_t *color_background);

#endif /* POLICE_H_ */
