/**
*@file BusCan.h
*@author Marques Rafael, Berger Antoine et Da Silva David
*@version 1.0
*@date 1 avril 2014
*@brief content constants and header of functions used on BusCan.h
*/

#ifndef BusCan_h_
#define BusCan_h_

#include "LPC17xx.h"

typedef struct{
	uint32_t id_Bus;
	uint8_t dlc;
	uint8_t data[8];
}str_bus;

void Init_BusCan();
void Write_BusCan();
void Read_BusCan();

#endif /* BusCan_h_ */
