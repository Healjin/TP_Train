/*
 *@file drawScreen.h
 *@author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 *@version 1.0
 *@date 19 June 2014
 *@briefs Contain functions to draws things on the screen.
 */

#ifndef DRAWSCREEN_H_
#define DRAWSCREEN_H_

#include "LPC17xx.h"
#include "ExtLab2.h"
#include "Ecran.h"
#include <cr_section_macros.h>

void change_zone_color(uint16_t x_start, uint16_t x_stop, uint16_t y_start, uint16_t y_stop, uint8_t *color_character);
void draw_arrow_right(uint16_t x_start, uint16_t y_start, uint8_t thickness, uint8_t heigth_arrow, uint8_t length,
		uint8_t *color);
void draw_arrow_left(uint16_t x_start, uint16_t y_start, uint8_t thickness, uint8_t heigth_arrow, uint8_t length,
		uint8_t *color);
void display_lights(uint8_t *color, uint8_t length);


#endif /* DRAWSCREEN_H_ */
