/*
 *@file SD.c
 *@author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 *@version 1.0
 *@date 19 June 2014
 *@briefs Contain functions to init SD card, read blocs on SD card.
 */

#include "SD.h"
int x, i, y, data, k, l = 0;
uint8_t rep;
int reponse[512];
uint8_t Tab[512];
/*
 *@briefs Chip Select
 */
void Clear_pin() {
	LPC_GPIO0->FIOCLR = 1 << 10;
	Valide_datas_bus_to_extlab2();
}
/*
 *@briefs Chip Select
 */
void Set_pin() {
	LPC_GPIO0->FIOSET = 1 << 10;
	Valide_datas_bus_to_extlab2();
}

/*
 *@briefs Read a block on the SD card by sending CMD17 command on SPI
 *@brief stock block on array
 *@param n_block Is the block you want to read
 */
void Read_SD_one_block(uint32_t n_block) {

	Select_control_bus();

	rep = Write_Read_SPI_8bits(0xff);
	Clear_pin();

	//send CMD17 command
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
/*
 *@briefs Read multiple blocks on SD card by using Read_SD_one_block function
 *@brief chose an interval with a starting block and end block
 *@param n_block_depart Starting block
 *@param n_block_arrive End block
 */
void Read_SD_multi_block(uint32_t n_block_depart,uint32_t n_block_arrive) {
	uint8_t offset = 0; int i = 0;
	k = 0;
	uint8_t pixel_to_next_page[2];
	for (y = n_block_depart; y <= n_block_arrive; y++) {
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
/*
 *@briefs Write on SD card -----THIS FUNCTION DOESN'T WORK-----------
 *@brief Function isn't necesary in our work
 */
void Write_SD() {

	rep = Write_Read_SPI_8bits(0xff);
	Clear_pin();

	//Send CMD24 command
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
	Select_control_bus();
	Valide_datas_bus_to_extlab2();
}
/*
 *@briefs SPI initialisation on SD card
 *@brief Send different Command with SPI protocol on SD card 
 *@brief Set SPI frequency for initialisation only
 *@brief Protocol initialisation is describe step by step on our document (scheme)
 */
void init_SD() {
	int x = 0;
	int y = 0;
	int i = 0;

	int Tab[5] = { 0, 0, 0, 0, 0 }; // arry used for SPI return

	ChipSetSelect();

	Change_Frequency_SPI(400000); //Set SPI frequency for initialisation
	

	LPC_GPIO0->FIODIR |= 1 << 10; 
	Clear_pin();

	//Waiting for 80 tick on SPI before sending command
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

	//Waiting for 24 tick on SPI before sending command
	Write_only_SPI_8bits(0xFF);
	Write_only_SPI_8bits(0xFF);

	//sending CMD0 command
	Clear_pin();
	Write_only_SPI_8bits(0b01000000); //startBit + Transmission+ CMD
	Write_only_SPI_8bits(0b00000000); //argument
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //argument end
	Write_only_SPI_8bits(0b10010101); // CRC7 + endBit
	do {
		rep = Write_Read_SPI_8bits(0xFF);
	} while (rep >> 7); // check if bit 7 is OK

	Set_pin();
	rep = Write_Read_SPI_8bits(0xff);

	//while IDLE <> 0 send CMD
	do {
		Clear_pin();

		//send CMD55 command before sending ACMD41 command

		Write_only_SPI_8bits(0b01110111); //startBit + Transmission+ CM
		Write_only_SPI_8bits(0b00000000); //argument
		Write_only_SPI_8bits(0b00000000); //
		Write_only_SPI_8bits(0b00000000); //
		Write_only_SPI_8bits(0b00000000); //argument end
		Write_only_SPI_8bits(0b00000001); // CRC7 + endBit
		do {
			rep = Write_Read_SPI_8bits(0xff);
		} while (rep >> 7); // check if bit 7 is OK

		Set_pin();

		Write_Read_SPI_8bits(0xff);

		Clear_pin();

		//sending ACMD41 command
		Write_only_SPI_8bits(0b01101001); //startBit + Transmission+ CM
		Write_only_SPI_8bits(0b00000000); //argument
		Write_only_SPI_8bits(0b00000000); //
		Write_only_SPI_8bits(0b00000000); //
		Write_only_SPI_8bits(0b00000000); //argument end
		Write_only_SPI_8bits(0b00000001); // CRC7 + endBit
		do {
			rep = Write_Read_SPI_8bits(0xff);
		} while (rep >> 7); // check if bit 7 is OK

		Set_pin();
		Write_Read_SPI_8bits(0xff);

	} while (rep & 1); //end while

	Clear_pin();

	//sending CMD58 command
	Write_only_SPI_8bits(0b01111010); //startBit + Transmission+ CM
	Write_only_SPI_8bits(0b00000000); //argument
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //
	Write_only_SPI_8bits(0b00000000); //argument end
	Write_only_SPI_8bits(0b00000001); // CRC7 + endBit

	do {
		rep = Write_Read_SPI_8bits(0xff);
	} while (rep >> 7); // check if bit 7 is OK
	Tab[0] = x;
	for (i = 1; i < 5; i++) {
		x = Write_Read_SPI_8bits(0xff); //Stock SPI return on array to check condition 
		Tab[i] = x;
	}

	Set_pin();
	y = Tab[2];

	if ((y & (1 << 6)) | (y & (1 << 7))) {
		Change_Frequency_SPI(5000000); // set frequency to the one you want
	}
}
