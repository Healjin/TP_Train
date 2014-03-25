/**
*@file SPI.h
*@author Swagteam
*@version 1.0
*@date 11 march 2014
*@brief content constants and header of functions used on SPI.c
*/
#ifndef SPI_H_
#define SPI_H_

#include "LPC17xx.h"
#include <cr_section_macros.h>

/* -- SPCR register -- */
#define BIT_ENABLE 2
#define CPHA 3
#define CPOL 4
#define MODE_SELECT 5
#define SPIF 7


void Write_only_SPI_8bits(uint8_t datas);
uint8_t Write_Read_SPI_8bits(uint8_t datas);
void Init_SPI_master_mode(uint8_t S_CPHA, uint8_t S_CPOL, uint32_t SPI_rate, uint8_t _16_or_8bits_com);


#endif /* SPI_H_ */
