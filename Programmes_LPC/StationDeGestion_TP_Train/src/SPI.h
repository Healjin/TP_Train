/**
 *@file SPI.h
 *@author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 *@version 1.0
 *@date 19 June 2014
 *@brief Contain all function to communication with the SPI.
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

void Write_only_SPI_8bits(uint8_t data);
uint8_t Write_Read_SPI_8bits(uint8_t data);
void Init_SPI_master_mode(uint8_t S_CPHA, uint8_t S_CPOL, uint32_t SPI_rate, uint8_t _16_or_8bits_com);
void Change_Frequency_SPI(uint32_t SPI_rate);

#endif /* SPI_H_ */
