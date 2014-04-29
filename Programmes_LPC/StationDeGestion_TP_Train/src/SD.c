/*
*@file SD.c
*@author Swagteam
*@version 1.0
*@date 8 april 2014
*@brief SD configuration
*/
#include "SD.h";
void init_SD(){
	int x=0;
	int error = 0;
	int Table_SPDR[40] = {0};
	uint64_t R3 = 0

//assert CS
	LPC_GPIO0->FIODIR |= 1 << 10;
	LPC_GPIO0->FIOCLR = 1 << 10;


//delay 74 clocks
	Write_only_SPI_8bits(0b00000000);
	Write_only_SPI_8bits(0b00000000);
	Write_only_SPI_8bits(0b00000000);
	Write_only_SPI_8bits(0b00000000);
	Write_only_SPI_8bits(0b00000000);
	Write_only_SPI_8bits(0b00000000);
	Write_only_SPI_8bits(0b00000000);
	Write_only_SPI_8bits(0b00000000);


//deassert CS
	LPC_GPIO0->FIOSET |= 1 << 10;


//delay 16 clocks
	Write_only_SPI_8bits(0b00000000);
	Write_only_SPI_8bits(0b00000000);


//CMD0
	LPC_GPIO0->FIOCLR = 1 << 10;
	Write_only_SPI_8bits(0b01000000);//47--40 start bit and transmission bit
	Write_only_SPI_8bits(0b00000000);//39-32
	Write_only_SPI_8bits(0b00000000);//31--24
	Write_only_SPI_8bits(0b00000000);//23--16
	Write_only_SPI_8bits(0b00000000);//15--8
	Write_only_SPI_8bits(0b10010101);//7--0

	x = Write_Read_SPI_8bits(0b00000000);



//If idle = 0 then CMD58 else go to ACMD41
	do{

	//CMD55
	Write_only_SPI_8bits(0b01111011);//47--40 start bit and transmission bit
	Write_only_SPI_8bits(0b00000000);//39-32
	Write_only_SPI_8bits(0b00000000);//31--24
	Write_only_SPI_8bits(0b00000000);//23--16
	Write_only_SPI_8bits(0b00000000);//15--8
	Write_only_SPI_8bits(0b00000001);//7--0

	//ACMD41
	Write_only_SPI_8bits(0b00101001);//47--40 start bit and transmission bit
	Write_only_SPI_8bits(0b00000000);//39-32
	Write_only_SPI_8bits(0b00000000);//31--24
	Write_only_SPI_8bits(0b00000000);//23--16
	Write_only_SPI_8bits(0b00000000);//15--8
	Write_only_SPI_8bits(0b00000001);//7--0

	}while(LPC_SPI->SPDR & (1 << 10));


	//CMD58
	Write_only_SPI_8bits(0b00111010);//47--40 start bit and transmission bit
	Write_only_SPI_8bits(0b00000000);//39-32
	Write_only_SPI_8bits(0b00000000);//31--24
	Write_only_SPI_8bits(0b00000000);//23--16
	Write_only_SPI_8bits(0b00000000);//15--8
	Write_only_SPI_8bits(0b00000001);//7--0

	for(i=0;i<5;i++){

	}

// if 3.3V allowed then Return ok else return error exit
	if(LPC_SPI->SPDR & (1 << 20)){
		//set clock to maximum

	}else{
		error = 1;
	}

//Return OK




}

