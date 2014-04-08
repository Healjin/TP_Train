/*
*@file main.c
*@author Swagteam
*@version 1.0
*@date 1 april 2014
*@brief main definition
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "Ecran.h"
#include "police.h"
//#include "mario.h"
#include "SPI.h"
#include "Touchscreen.h"
#endif

int flag_interrupt = 0;


/**
*@brief Interuption Timer 3
*
*/
void EINT3_IRQHandler(void)
{
	/* -- Clear interrupt on the touchscreen -- */
	LPC_GPIOINT->IO2IntClr |= 1 << 10;

	flag_interrupt = 1;
}


//const tImage mario = {image_data_mario, 320, 240};

int main(void) {

	Init_display();
	Select_display_bus();
	Set_cursor(0,0);
	/* -- All screen selected -- */
	/* Display size = 320x240 */
	Create_partial_screen(0, 319, 0, 239);

	/* -- Set the "background" on the LCD -- */
	int var;
	for (var = 0; var < 320*240; var++) {
		Write_pixel(255,255,255);
	}


	Create_button(100,100,50,100);  // x,y, largeur, hauteur




	uint8_t red[3]={255,0,0};
	uint8_t green[3]={0,255,0};
	uint8_t blue[3]={0,0,255};
	/* -- Test text -- */
	//Write_string_with_background("Animaux",10,10,red,green);
	//Write_string("MmmMmVvfNNnn",20,300,blue);

	//Set_Button(0,100,0,100);

	/* -- Test to draw an image on the display -- */
	//Select_display_bus();
	//Draw_Image(&mario);

	/* -- Test writing letter -- */
	/*uint8_t color[3] = {255,255,255};
	uint8_t color_back[3] = {0,0,255};
	Write_char_with_background('A',90,0,color,color_back);*/

	/* -- Test touchscreen -- */
	//Init_touchscreen();
	//Init_SPI_master_mode(0, 0, 100000, 8);

<<<<<<< HEAD
    /* -- Test writing letter without background -- */
	//Select_display_bus();
	//uint8_t color2[3] = {0,0,0};
	//Write_char('B',200,200,red);

=======
>>>>>>> fbab48245a4d1eacf5781cf37b76ddf841ab10ca
	while(1) {
		if(flag_interrupt == 1)
		{
			uint16_t x = 0;
			uint16_t y = 0;

			Read_x_and_y_12bits(&x, &y);

			uint32_t y_pixel = (240*(uint32_t)x)/4096;
			uint32_t x_pixel = 320 - (320*(uint32_t)y)/4096;
			Select_display_bus();
			uint8_t color_back[3] = {0,0,255};
			Write_char('A',5,290,color_back);
			Set_cursor(y_pixel, x_pixel);
			Write_pixel(0,0,0);
			Set_cursor(y_pixel+1, x_pixel);
			Write_pixel(0,0,0);
			Set_cursor(y_pixel, x_pixel+1);
			Write_pixel(0,0,0);
			Set_cursor(y_pixel+1, x_pixel+1);
			Write_pixel(0,0,0);
			flag_interrupt = 0;
		}
	}
	return 0 ;
}
