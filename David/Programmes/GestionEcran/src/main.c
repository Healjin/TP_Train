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
#endif

// TODO: insert other include files here

// TODO: insert other definitions and declarations here




int main(void) {

	// TODO: insert code here
	Init_display();
	Set_cursor(50,50);
	Create_partial_screen(50, 100, 50,100);
	while(1) {
		Write_pixel(255,0,0);
	}
	return 0 ;
}
