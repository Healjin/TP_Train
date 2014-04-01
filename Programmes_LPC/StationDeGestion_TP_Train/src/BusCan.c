/*
*@file BusCan.c
*@author Swagteam
*@version 1.0
*@date 1 april 2014
*@brief BusCan configuration
*/
#include "BusCan.h"

void Init_BusCan(){
	LPC_GPIO0->PCCAN1 |= 0x1 << 13;
	LPC_GPIO0->PCLK_CAN1  |= 0x00 << 26;
	LPC_GPIO0->PINSEL0
	LPC_GPIO0->PINMODE0
}
