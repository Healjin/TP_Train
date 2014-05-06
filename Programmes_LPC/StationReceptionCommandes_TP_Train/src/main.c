/**
 *@file main.c
 *@author Swagteam
 *@version 1.0
 *@date 29 avril 2014
 *@brief content constants and header of functions used on BusCan.h
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "BusCan.h"
#include <cr_section_macros.h>
#endif


int main(void) {
	str_bus str;
	Init_BusCan();

	str.id_Bus = 0x00004711;
	str.dlc = 0x5;
	str.data = 0;
	while(1)
	{
		//while((LPC_CAN1->GSR & 0x1 << 3) == 0);
		str.data ^=1;
		Write_BusCan(&str);
	}
}
