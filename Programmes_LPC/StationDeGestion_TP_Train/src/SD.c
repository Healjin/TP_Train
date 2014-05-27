
#include "SPI.h"
#include "SD.h"
int x,i =0;
uint8_t rep;
int reponse[512];

void Read_SD(){

		rep = Write_Read_SPI_8bits(0xff);
		LPC_GPIO0 -> FIOCLR= 1 << 10;
		LPC_GPIO2 ->FIOSET = 0b1 << 8;
		LPC_GPIO2 ->FIOCLR = 0b1 << 8;

		//Envoie de la CMD17
		Write_only_SPI_8bits(0b01010001);//startBit + Transmission+ CM
		Write_only_SPI_8bits(0b00000000);//argument
		Write_only_SPI_8bits(0b00000000);//
		Write_only_SPI_8bits(0b00000000);//
		Write_only_SPI_8bits(0b00000000);//fin argument
		Write_only_SPI_8bits(0b00000001);// CRC7 + endBit
		do{
			rep = Write_Read_SPI_8bits(0xff);
		} while (rep!=0);

		LPC_GPIO0 -> FIOSET= 1 << 10;
		LPC_GPIO2 ->FIOSET = 0b1 << 8;
		LPC_GPIO2 ->FIOCLR = 0b1 << 8;

		LPC_GPIO0 -> FIOCLR= 1 << 10;
		LPC_GPIO2 ->FIOSET = 0b1 << 8;
		LPC_GPIO2 ->FIOCLR = 0b1 << 8;
		//boucle while jusqua FE
		//lire 512  +  2 ??
		//creation tableau
		for(i=0;i<513;i++){
			Write_Read_SPI_8bits(0xff);
		}

		LPC_GPIO0 -> FIOSET= 1 << 10;
				LPC_GPIO2 ->FIOSET = 0b1 << 8;
				LPC_GPIO2 ->FIOCLR = 0b1 << 8;


}

void ChipSetSelect(){

	LPC_GPIO0 -> FIODIR |= 0b11 << 21;
	LPC_GPIO0 -> FIOSET = 0b11 << 21;
	LPC_GPIO2 ->FIODIR |= 0b1 << 8;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
}

void init_SD(){
	int x=0;
	int y=0;
	int i=0;


	int Tab[5]={0,0,0,0,0};

	//int IDLE;

	ChipSetSelect();
	Init_SPI_master_mode(0, 0, 400000, 8);

	LPC_GPIO0 -> FIODIR |= 1 << 10;// met la pin en sortie
	LPC_GPIO0 -> FIOCLR= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//80 coups d'horloges
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);


	LPC_GPIO0 -> FIOSET = 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	// 24 coups d'horloges
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);
//	write_SPI(0b00000000);
//	write_SPI(0b00000000);
//	write_SPI(0b00000000);

//	do{
	//Envoie de la CMD0
	LPC_GPIO0 -> FIOCLR= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	Write_only_SPI_8bits(0b01000000);//startBit + Transmission+ CMD
	Write_only_SPI_8bits(0b00000000);//argument
	Write_only_SPI_8bits(0b00000000);//
	Write_only_SPI_8bits(0b00000000);//
	Write_only_SPI_8bits(0b00000000);//fin argument
	Write_only_SPI_8bits(0b10010101);// CRC7 + endBit
	do{
	rep = Write_Read_SPI_8bits(0xFF);
	} while (rep>>7);

	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	rep = Write_Read_SPI_8bits(0xff);

	//	}while (x != 1);
	//tant que IDLE <> 0 renvoyer les CMD
	do {
		LPC_GPIO0 -> FIOCLR= 1 << 10;
		LPC_GPIO2 ->FIOSET = 0b1 << 8;
		LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//Envoie de la CMD55 pour pouvoir envoyer ACMD41
//	do{
		Write_only_SPI_8bits(0b01110111);//startBit + Transmission+ CM
		Write_only_SPI_8bits(0b00000000);//argument
		Write_only_SPI_8bits(0b00000000);//
		Write_only_SPI_8bits(0b00000000);//
		Write_only_SPI_8bits(0b00000000);//fin argument
		Write_only_SPI_8bits(0b00000001);// CRC7 + endBit
	do{
	rep = Write_Read_SPI_8bits(0xff);
	} while (rep>>7);


	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	Write_Read_SPI_8bits(0xff);
//	}while(x !=0);

	LPC_GPIO0 -> FIOCLR= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//Envoie de la ACMD41
	Write_only_SPI_8bits(0b01101001);//startBit + Transmission+ CM
	Write_only_SPI_8bits(0b00000000);//argument
	Write_only_SPI_8bits(0b00000000);//
	Write_only_SPI_8bits(0b00000000);//
	Write_only_SPI_8bits(0b00000000);//fin argument
	Write_only_SPI_8bits(0b00000001);// CRC7 + endBit
	do{
	rep = Write_Read_SPI_8bits(0xff);
	} while (rep>>7);

	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;
	Write_Read_SPI_8bits(0xff);

	} while(rep&1) ; //end while


	LPC_GPIO0 -> FIOCLR= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	//Envoie CMD 58
	Write_only_SPI_8bits(0b01111010);//startBit + Transmission+ CM
	Write_only_SPI_8bits(0b00000000);//argument
	Write_only_SPI_8bits(0b00000000);//
	Write_only_SPI_8bits(0b00000000);//
	Write_only_SPI_8bits(0b00000000);//fin argument
	Write_only_SPI_8bits(0b00000001);// CRC7 + endBit

	do{
	rep = Write_Read_SPI_8bits(0xff);
	} while (rep>>7);
	Tab[0]=x;
	for ( i=1;i<5; i++){
		x=Write_Read_SPI_8bits(0xff);
		Tab[i]=x;
		}

	LPC_GPIO0 -> FIOSET= 1 << 10;
	LPC_GPIO2 ->FIOSET = 0b1 << 8;
	LPC_GPIO2 ->FIOCLR = 0b1 << 8;

	y = Tab[2];


	 if((y & (1<<6))| (y& (1<<7))){
		 Init_SPI_master_mode(0, 0, 300000, 8);
	}



}






