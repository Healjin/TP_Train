/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "Ecran.h"
#include "police.h"
//#include "mario.h"
#endif


int main(void) {

	Init_display();
	Set_cursor(0,0);
	Create_partial_screen(0, 319, 0, 239);

	/* Display size = 320x240 */
	// All screen unlock
	// Create_partial_screen(0, 319, 0, 239);

	/*Set the "background" on the LCD*/
	int var;
	for (var = 0; var < 320*240; var++) {
		Write_pixel(0,0,0);
	}

	/* -- Test to draw an image on the diplay -- */
	//Draw_Images(&mario);

	/* -- Test writing letter -- */

	/*uint8_t color[3] = {255,255,255};
	uint8_t color_back[3] = {0,0,255};
	Write_char_with_background('A',90,0,color,color_back); */

    /* -- Test writting letter without blackground -- */
	/*uint8_t color2[3] = {255,255,255};
	Write_char('B',90,90,color2);*/

	while(1) {
	}
	return 0 ;
}
