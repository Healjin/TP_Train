/*
*@file police.h
*@author Swagteam
*@version 1.0
*@date 11 march 2014
*@brief content constants and header of functions used on police.c
*/
#ifndef SD_H_
#define SD_H_

#include "LPC17xx.h"
#include <cr_section_macros.h>
#include "SPI.h"
#include "ExtLab2.h"
#include "Ecran.h"
void init_SD();
void Read_SD_one_block();
void Read_SD_multi_block(uint32_t n_block);
void Clear_pin();
void Set_pin();
void Write_SD();
void Read_SD_multiBLocks();

#endif /* POLICE_H_ */
