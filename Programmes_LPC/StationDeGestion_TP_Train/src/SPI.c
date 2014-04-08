/**
*@file SPI.h
*@author Swagteam
*@version 1.0
*@date 14 march 2014
*@brief
*/
#include "SPI.h"

/**
*@brief Initialization of master mode on SPI
*@param S_CPHA  -->  clock phase control
*@param S_CPOL  -->  rising/failing edge
*@param SPI_rate  -->  rate of SPI
*@param _16_or_8bits_com
*/
void Init_SPI_master_mode(uint8_t S_CPHA, uint8_t S_CPOL, uint32_t SPI_rate, uint8_t _16_or_8bits_com)
{
	LPC_PINCON->PINSEL0 |= 0x3 << 30; // Enable SCK
	LPC_PINCON->PINSEL1 |= 0x3C; // Enable MISO and MOSI

	if(_16_or_8bits_com == 8)
		LPC_SPI->SPCR &=~ BIT_ENABLE; // set 8bits mode on SPI
	else
		LPC_SPI->SPCR |= BIT_ENABLE; // set 16bits mode on SPI

	LPC_SPI->SPCR |= 1 << MODE_SELECT; // configure spi on master mode


	uint16_t div = (SystemCoreClock/4) / SPI_rate;
	if (div % 2)
		LPC_SPI->SPCCR = div + 1;
	else
		LPC_SPI->SPCCR = div;
}
/**
*@brief
*@param datas  -->
*/
void Write_only_SPI_8bits(uint8_t datas)
{
	LPC_SPI->SPDR = datas;
	/* Wait the end of transmission */
	while(!(LPC_SPI->SPSR & (1 << SPIF)));
}
/**
*@brief
*@param datas  -->
*/
uint8_t Write_Read_SPI_8bits(uint8_t datas)
{
	LPC_SPI->SPDR = datas;
	/* Wait the end of transmission */
	while((LPC_SPI->SPSR & (1 << SPIF)) == 0);
	return LPC_SPI->SPDR;
}
