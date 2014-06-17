#include "SD.h"
int x, i, y, data, k, l = 0;
uint8_t rep;
int reponse[512];
uint8_t Tab[512];

void Clear_pin() {
	LPC_GPIO0->FIOCLR = 1 << 10;
	Valide_datas_bus_to_extlab2();
}

void Set_pin() {
	LPC_GPIO0->FIOSET = 1 << 10;
	Valide_datas_bus_to_extlab2();
}

void Read_SD_one_block(uint32_t n_block) {

	Select_control_bus();

	rep = Write_Read_SPI_8bits(0xff);
	Clear_pin();

	//Envoie de la CMD17
	Write_only_SPI_8bits(0b01010001); //startBit + Transmission+ CM

	uint32_t arg = n_block * 512;
	Write_only_SPI_8bits(arg >> 24); //argument
	Write_only_SPI_8bits(arg >> 16); //
	Write_only_SPI_8bits(arg >> 8); //
	Write_only_SPI_8bits(arg); //fin argument

	Write_only_SPI_8bits(0b00000001); // CRC7 + endBit
	do {
		rep = Write_Read_SPI_8bits(0xff);
	} while (rep != 0);

	Set_pin();
	Clear_pin();

	while (rep != 0xFE) {
		rep = Write_Read_SPI_8bits(0xff);
	}

	for (i = 0; i < 514; i++) {
		data = Write_Read_SPI_8bits(0xff);
		if (i < 512) {
			Tab[i] = data;
		}
	}
	Set_pin();
}

void Read_SD_multi_block(uint32_t n_block_depart,uint32_t n_block_arrive) {
	uint8_t offset = n_block_depart; int i;
	uint8_t pixel_to_next_page[2];
	for (y = n_block_depart; y < n_block_arrive; y++) {
		Read_SD_one_block(y);

		Select_display_bus();

		if((y > n_block_depart) && (offset == 1))
			Write_pixel(Tab[1],Tab[0],pixel_to_next_page[1]);
		else if ((y > n_block_depart) && (offset == 0))
			Write_pixel(Tab[0],pixel_to_next_page[1],pixel_to_next_page[0]);

		if(y > n_block_depart)
		{
			offset = (offset + 1) % 3;
			k = offset;
		}

		for (; k < (510 + offset); k = k + 3) {
			Write_pixel(Tab[k + 2], Tab[k + 1], Tab[k]);
		}

		for(i=offset; i < 2; i++)
			pixel_to_next_page[i] = Tab[510 + i];
	}
}

void Write_SD() {

	rep = Write_Read_SPI_8bits(0xff);
	Clear_pin();

	//Envoie de la CMD24
	Write_only_SPI_8bits(0b01011000); //startBit + Transmission+ CM
	Write_only_SPI_8bits(0b00000000); //argument
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //fin argument
	Write_only_SPI_8bits(0b00000001); // CRC7 + endBit
	do {
		rep = Write_Read_SPI_8bits(0xff);
	} while (rep != 0);

	Set_pin();
	Clear_pin();

	Write_only_SPI_8bits(0xFE);

	for (i = 0; i < 514; i++) {

		Write_only_SPI_8bits(0x56);

	}
	Set_pin();

}

void ChipSetSelect() {

	/*LPC_GPIO0 -> FIODIR |= 0b11 << 21;
	 LPC_GPIO0 -> FIOSET = 0b11 << 21;*/
	Select_control_bus();
	Valide_datas_bus_to_extlab2();
	/*LPC_GPIO2 ->FIODIR |= 0b1 << 8;
	 LPC_GPIO2 ->FIOSET = 0b1 << 8;
	 LPC_GPIO2 ->FIOCLR = 0b1 << 8;*/
}

void init_SD() {
	int x = 0;
	int y = 0;
	int i = 0;

	int Tab[5] = { 0, 0, 0, 0, 0 };

	ChipSetSelect();

	Change_Frequency_SPI(400000);
	//Init_SPI_master_mode(0, 0, 400000, 8);

	LPC_GPIO0->FIODIR |= 1 << 10; // met la pin en sortie
	Clear_pin();

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

	Set_pin();

	// 24 coups d'horloges
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);

	//Envoie de la CMD0
	Clear_pin();
	Write_only_SPI_8bits(0b01000000); //startBit + Transmission+ CMD
	Write_only_SPI_8bits(0b00000000); //argument
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //fin argument
	Write_only_SPI_8bits(0b10010101); // CRC7 + endBit
	do {
		rep = Write_Read_SPI_8bits(0xFF);
	} while (rep >> 7);

	Set_pin();
	rep = Write_Read_SPI_8bits(0xff);

	//tant que IDLE <> 0 renvoyer les CMD
	do {
		Clear_pin();

		//Envoie de la CMD55 pour pouvoir envoyer ACMD41

		Write_only_SPI_8bits(0b01110111); //startBit + Transmission+ CM
		Write_only_SPI_8bits(0b00000000); //argument
		Write_only_SPI_8bits(0b00000000); //
		Write_only_SPI_8bits(0b00000000); //
		Write_only_SPI_8bits(0b00000000); //fin argument
		Write_only_SPI_8bits(0b00000001); // CRC7 + endBit
		do {
			rep = Write_Read_SPI_8bits(0xff);
		} while (rep >> 7);

		Set_pin();

		Write_Read_SPI_8bits(0xff);

		Clear_pin();

		//Envoie de la ACMD41
		Write_only_SPI_8bits(0b01101001); //startBit + Transmission+ CM
		Write_only_SPI_8bits(0b00000000); //argument
		Write_only_SPI_8bits(0b00000000); //
		Write_only_SPI_8bits(0b00000000); //
		Write_only_SPI_8bits(0b00000000); //fin argument
		Write_only_SPI_8bits(0b00000001); // CRC7 + endBit
		do {
			rep = Write_Read_SPI_8bits(0xff);
		} while (rep >> 7);

		Set_pin();
		Write_Read_SPI_8bits(0xff);

	} while (rep & 1); //end while

	Clear_pin();

	//Envoie CMD 58
	Write_only_SPI_8bits(0b01111010); //startBit + Transmission+ CM
	Write_only_SPI_8bits(0b00000000); //argument
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //fin argument
	Write_only_SPI_8bits(0b00000001); // CRC7 + endBit

	do {
		rep = Write_Read_SPI_8bits(0xff);
	} while (rep >> 7);
	Tab[0] = x;
	for (i = 1; i < 5; i++) {
		x = Write_Read_SPI_8bits(0xff);
		Tab[i] = x;
	}

	Set_pin();

	y = Tab[2];

	if ((y & (1 << 6)) | (y & (1 << 7))) {
		Change_Frequency_SPI(5000000);
		//Init_SPI_master_mode(0, 0, 5000000, 8);
	}
}

