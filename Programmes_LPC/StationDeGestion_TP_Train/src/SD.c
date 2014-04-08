/*
*@file SD.c
*@author Swagteam
*@version 1.0
*@date 8 april 2014
*@brief SD configuration
*/
#include "SD.h";
void init_SD(){

//Set SPI clock to 400khz
	LPC_SPI->SPCCR = 64;
//assert CS
	LPC_GPIO0->FIODIR |= 1 << 10;
	LPC_GPIO0->FIOCLR = 1 << 10;
//delay 74 clocks
	int i;
	for(i=0;i<10000;i++);
	i=0;
//deassert CS
	LPC_GPIO0->FIOSET |= 1 << 10;
//delay 16 clocks
	for(i=0;i<10000;i++);
	i=0;

//CMD0
	LPC_GPIO0->FIOCLR = 1 << 10;
	Write_only_SPI_8bits(0b01000000);//47--40 start bit and transmission bit
	Write_only_SPI_8bits(0b00000000);//39-32
	Write_only_SPI_8bits(0b00000000);//31--24
	Write_only_SPI_8bits(0b00000000);//23--16
	Write_only_SPI_8bits(0b00000000);//15--8
	Write_only_SPI_8bits(0b10010101);//7--0

	int x = Write_Read_SPI_8bits(0b00000000);
//CMD41
	Write_only_SPI_8bits(0b01101001);//47--40 start bit and transmission bit
	Write_only_SPI_8bits(0b00000000);//39-32
	Write_only_SPI_8bits(0b00000000);//31--24
	Write_only_SPI_8bits(0b00000000);//23--16
	Write_only_SPI_8bits(0b00000000);//15--8
	Write_only_SPI_8bits(0b10010101);//7--0
//CMD55
	Write_only_SPI_8bits(0b01111011);//47--40 start bit and transmission bit
	Write_only_SPI_8bits(0b00000000);//39-32
	Write_only_SPI_8bits(0b00000000);//31--24
	Write_only_SPI_8bits(0b00000000);//23--16
	Write_only_SPI_8bits(0b00000000);//15--8
	Write_only_SPI_8bits(0b10010101);//7--0
//If idle = 0 then CMD58 else go to CMD41
//CMD58
// if 3.3V allowed then Return ok else return error exit
//Return OK
//set clock to maximum



}

