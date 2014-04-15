/**
*@file BusCan.h
*@author Swagteam
*@version 1.0
*@date 11 march 2014
*@brief content constants and header of functions used on BusCan.h
*/

#ifndef BusCan_h_
#define BusCan_h_

#include "LPC17xx.h"
#include <cr_section_macros.h>
#define BRP 4					//BR = CAN_CLK/(BRP + 1)(20)

void Init_BusCan();
void Write_BusCan();
void Read_BusCan();

#endif /* BusCan_h_ */
