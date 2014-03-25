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
#include "SPI.h"
#include "Touchscreen.h"
#endif

int flag_interrupt = 0;

void EINT3_IRQHandler(void)
{
	//uint8_t test1 = Write_Read_SPI_8bits(0x80|0x10); // Send options
	//uint8_t test2 = Write_Read_SPI_8bits(0x00);
	//uint8_t test3 = Write_Read_SPI_8bits(0x80|0x10);


	/* -- Clear interrupt on the touchscreen -- */
	LPC_GPIOINT->IO2IntClr |= 1 << 10;

	flag_interrupt = 1;
}


//const tImage mario = {image_data_mario, 320, 240};

int main(void) {

	Init_display();
	Set_cursor(0,0);
	/* -- All screen selected -- */
	/* Display size = 320x240 */
	Create_partial_screen(0, 319, 0, 239);

	/* -- Set the "background" on the LCD -- */
	int var;
	for (var = 0; var < 320*240; var++) {
		Write_pixel(0,255,0);
	}

	/* -- Test to draw an image on the display -- */
	//Select_display_bus();
	//Draw_Image(&mario);

	/* -- Test writing letter -- */
	uint8_t color[3] = {255,255,255};
	uint8_t color_back[3] = {0,0,255};
	Write_char_with_background('A',90,0,color,color_back);


    /* -- Test writing letter without background -- */
	uint8_t color2[3] = {255,255,255};
	Write_char('B',90,90,color2);

	/* -- Test pressing on touchscreen, init interrupt -- */
	LPC_GPIO2->FIODIR |= 0b111 << 11; // Bit for select input
	LPC_GPIO2->FIOCLR = 0b111 << 11;
	LPC_GPIO2->FIOSET = 0b101 << 11;
	LPC_GPIO2->FIODIR &=~ (1 << IRQ_Touchscreen);

	NVIC_EnableIRQ(EINT3_IRQn);
	LPC_GPIOINT->IO2IntEnF |= 1 << 10;


	/* -- SPI for touchscreen -- */
	Select_control_bus();
	LPC_GPIO0->FIODIR |= 1<<8;
	LPC_GPIO0->FIOSET = 1 << 8; // Select (/CS) touchscreen
	Valide_datas_bus_to_extlab2();
	Init_SPI_master_mode(0, 0, 100000, 8);
	LPC_PINCON->PINSEL0 |= 0x3 << 30; // SCK select
	LPC_PINCON->PINSEL1 |= 0xF << 2; // Select MOSI and MISO

	while(1) {
		if(flag_interrupt == 1)
		{

			LPC_GPIO0->FIOCLR = 1 << 8; // Select (/CS) touchscreen
			Valide_datas_bus_to_extlab2();

			uint8_t test2 = Write_Read_SPI_8bits(0xD3); // Send options
			uint8_t x_msb = Write_Read_SPI_8bits(0x00);
			uint8_t x_lsb = Write_Read_SPI_8bits(0x00);
			uint16_t x = x_lsb >> 3;
			x |= ((x_msb &~ 0x80) << 5);

			uint8_t test1 = Write_Read_SPI_8bits(0x92); // Send options
			uint8_t y_msb = Write_Read_SPI_8bits(0x00);
			uint8_t y_lsb = Write_Read_SPI_8bits(0x00);
			uint16_t y = y_lsb >> 3;
			y |= ((y_msb &~ 0x80) << 5);



			flag_interrupt = 0;

			LPC_GPIO0->FIOSET = 1 << 8; // Select (/CS) touchscreen
			Valide_datas_bus_to_extlab2();
		}
	}
	return 0 ;
}
