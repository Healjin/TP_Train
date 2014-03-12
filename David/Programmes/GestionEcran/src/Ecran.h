/*
 * Ecran.h
 *
 *  Created on: 4 mars 2014
 *      Author: David
 */

#ifndef ECRAN_H_
#define ECRAN_H_

#include "LPC17xx.h"
#include <cr_section_macros.h>

#define DISPLAY_CS 19
#define DISPLAY_RS 18
#define DISPLAY_WRB 20

void Init_ports_display();
void Index_out(uint8_t idx);
void Parameter_out(uint16_t param);
void Send_color(uint8_t color);
void Init_display();
void Write_pixel(uint8_t red,uint8_t green,uint8_t blue);
void Set_cursor(uint8_t x,uint8_t y);
void Create_partial_screen(uint16_t v_start, uint16_t v_end, uint8_t h_start, uint8_t h_end);



#endif /* ECRAN_H_ */
