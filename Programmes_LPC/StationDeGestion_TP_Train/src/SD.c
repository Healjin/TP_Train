/*
*@file SD.c
*@author Swagteam
*@version 1.0
*@date 8 april 2014
*@brief SD configuration
*/
#include "SD.h"
void init_SD(){
	Select_control_bus();
//assert CS
	LPC_GPIO0->FIODIR |= 1 << 10;
	LPC_GPIO0->FIOCLR = 1 << 10;
	Valide_datas_bus_to_extlab2();


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
	Valide_datas_bus_to_extlab2();


//delay 16 clocks
	Write_only_SPI_8bits(0b00000000);
	Write_only_SPI_8bits(0b00000000);


//CMD0
	LPC_GPIO0->FIOCLR = 1 << 10;
	Valide_datas_bus_to_extlab2();
	Write_only_SPI_8bits(0b01000000);//47--40 start bit and transmission bit
	Write_only_SPI_8bits(0b00000000);//39-32
	Write_only_SPI_8bits(0b00000000);//31--24
	Write_only_SPI_8bits(0b00000000);//23--16
	Write_only_SPI_8bits(0b00000000);//15--8
	Write_only_SPI_8bits(0b10010101);//7--0

	uint8_t x = Write_Read_SPI_8bits(0b00000000);



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

	}

//Return OK

	LPC_GPIO0->FIOSET |= 1 << 10;
	Valide_datas_bus_to_extlab2();
/*
 * /*
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


	int Tab[5]={0,0,0,0,0};

	//int IDLE;

	ChipSetSelect();
	init_spi(8, 64);



	LPC_GPIO0 -> FIODIR |= 1 << 10;// met la pin en sortie
	LPC_GPIO0 -> FIOCLR= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//80 coups d'horloges
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);


	LPC_GPIO0 -> FIOSET = 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	// 24 coups d'horloges
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);
	write_SPI(0b00000000);

	do{
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
	x= read_SPI();
	x= read_SPI();

	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;


	}while (x != 1);
	//tant que IDLE <> 0 renvoyer les CMD
	do {
		LPC_GPIO0 -> FIOCLR= 1 << 10;
		LPC_GPIO2 ->FIOSET = 0b1 << 8;
		LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//Envoie de la CMD55 pour pouvoir envoyer ACMD41
	do{
	write_SPI(0b01110111);//startBit + Transmission+ CM
	write_SPI(0b00000000);//argument
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//fin argument
	write_SPI(0b00000001);// CRC7 + endBit
	x=read_SPI();
	x=read_SPI();

	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	}while(x !=0);
	LPC_GPIO0 -> FIOCLR= 1 << 10;
		LPC_GPIO2 ->FIOSET = 0b1 << 8;
		LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	//Envoie de la ACMD41
	write_SPI(0b01101101);//startBit + Transmission+ CM
	write_SPI(0b00000000);//argument
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//
	write_SPI(0b00000000);//fin argument
	write_SPI(0b00000001);// CRC7 + endBit



	for ( i=0;i<5; i++){
		x=read_SPI();
		Tab[i]=x;
	}
	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	y = Tab[2];
	} while (((y & (0x01 <<6 )) != 1   |   (y & (0x01 <<7 ))!=1)); //end while


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

	LPC_GPIO0 -> FIOSET= 1 << 10;
		LPC_GPIO2 ->FIOSET = 0b1 << 8;
		LPC_GPIO2 ->FIOCLR = 0b1 << 8;


	// si 3V3 est bon change la CLK
	if ((x & (0x1 << 20))== 1) {
		 change_clock_spi(4);
	}else return 1;


	//
	LPC_GPIO0 -> FIOCLR= 1 << 10;
	return 0;


}
 *
 *
 */



}

