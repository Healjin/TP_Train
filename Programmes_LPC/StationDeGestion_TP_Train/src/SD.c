/*
*@file SD.c
*@author Swagteam
*@version 1.0
*@date 8 april 2014
*@brief SD configuration
*/
#include "SD.h"
void init_SD(){
	int x=0;
	int error = 0;
	int Table_SPDR[40] = {0};
	uint64_t R3 = 0;

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


// if 3.3V allowed then Return ok else return error exit
	if(LPC_SPI->SPDR & (1 << 20)){
		//set clock to maximum

	}else{
		error = 1;
	}

//Return OK

/*
/*
===============================================================================
 Name        : main.c
 Author      :
 Version     :
 Copyright   : Copyright (C)
 Description : main definition
===============================================================================

#include "spi.h"
#include "sd.h"



void ChipSetSelect(){

	LPC_GPIO0 -> FIODIR |= 0b11 << 21;

	LPC_GPIO0 -> FIOSET = 0b11 << 21;


	LPC_GPIO2 ->FIODIR |= 0b1 << 8;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
}



int Sd_initialisation(){
	int x=0;
	int y=0;
	int i=0;
	uint8_t rep;

	int Tab[5]={0,0,0,0,0};

	//int IDLE;

	ChipSetSelect();
	init_spi(8, 64);
	change_clock_spi(64);



	LPC_GPIO0 -> FIODIR |= 1 << 10;// met la pin en sortie
	LPC_GPIO0 -> FIOCLR= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//80 coups d'horloges
	write_SPI(0xFF);
	write_SPI(0xFF);
	write_SPI(0xFF);
	write_SPI(0xFF);
	write_SPI(0xFF);
	write_SPI(0xFF);
	write_SPI(0xFF);
	write_SPI(0xFF);
	write_SPI(0xFF);
	write_SPI(0xFF);


	LPC_GPIO0 -> FIOSET = 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	// 24 coups d'horloges
	write_SPI(0xFF);
	write_SPI(0xFF);
//	write_SPI(0b00000000);
//	write_SPI(0b00000000);
//	write_SPI(0b00000000);

//	do{
	//Envoie de la CMD0
	LPC_GPIO0 -> FIOCLR= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	write_SPI(0b01000000);//startBit + Transmission+ CMD
	write_SPI(0b00000000);//argument
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//fin argument
	write_SPI(0b10010101);// CRC7 + endBit
	do{
	rep = read_SPI();
	} while (rep>>7);

	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	rep = read_SPI();

	//	}while (x != 1);
	//tant que IDLE <> 0 renvoyer les CMD
	do {
		LPC_GPIO0 -> FIOCLR= 1 << 10;
		LPC_GPIO2 ->FIOSET = 0b1 << 8;
		LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//Envoie de la CMD55 pour pouvoir envoyer ACMD41
//	do{
	write_SPI(0b01110111);//startBit + Transmission+ CM
	write_SPI(0b00000000);//argument
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//fin argument
	write_SPI(0b00000001);// CRC7 + endBit
	do{
	rep = read_SPI();
	} while (rep>>7);


	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	read_SPI();
//	}while(x !=0);

	LPC_GPIO0 -> FIOCLR= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//Envoie de la ACMD41
	write_SPI(0b01101001);//startBit + Transmission+ CM
	write_SPI(0b00000000);//argument
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//fin argument
	write_SPI(0b00000001);// CRC7 + endBit
	do{
	rep = read_SPI();
	} while (rep>>7);

	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	read_SPI();

	} while(rep&1) ; //end while


	LPC_GPIO0 -> FIOCLR= 1 << 10;
			LPC_GPIO2 ->FIOSET = 0b1 << 8;
			LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//Envoie CMD 58
	write_SPI(0b01111010);//startBit + Transmission+ CM
	write_SPI(0b00000000);//argument
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//fin argument
	write_SPI(0b00000001);// CRC7 + endBit

	do{
	rep = read_SPI();
	} while (rep>>7);
	Tab[0]=x;
	for ( i=1;i<5; i++){
			x=read_SPI();
			Tab[i]=x;
		}

	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	y = Tab[2];


	 if((y & (1<<6))| (y& (1<<7))){
		 change_clock_spi(4);
	}else
		return 1;


	return 0;


}



*/


}

