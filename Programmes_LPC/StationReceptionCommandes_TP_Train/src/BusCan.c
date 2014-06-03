/*
*@file BusCan.c
*@author Swagteam
*@version 1.0
*@date 1 April 2014
*@brief BusCan configuration
*/
#include "BusCan.h"
/*
*@brief Initialization BusCan
*/
void Init_BusCan(){

	LPC_SC->PCONP |= 0x1 << 13;			//Power
	LPC_SC->PCLKSEL0 &=~ 0x00 << 26;	//Peripheral clock

	LPC_SC->PCLKSEL0 &=~ 0x00 << 28;	//Peripheral clock

	LPC_CAN1->MOD |= 0x01;
	LPC_CAN1->BTR = (12 << 16) + (5 << 20) + (3 << 14) + 4;		//TSEG1 = 12
	LPC_CAN1->MOD &=~ 0x01;

	LPC_PINCON->PINSEL0 |= 0x01;		//RD1
	LPC_PINCON->PINSEL0 |= 0x01 << 2;	//TD1

	LPC_CAN1->MOD &=~ 0x01;  			//Reset Mode
	LPC_CAN1->MOD &=~ 0x01 << 1;		//Listen Only Mode
	LPC_CAN1->MOD &=~ 0x01 << 2;		//Self Test Mode
	LPC_CAN1->MOD &=~ 0x01 << 3;		//Transmit Priority Mode
	LPC_CAN1->MOD &=~ 0x01 << 4;		//Sleep Mode
	LPC_CAN1->MOD &=~ 0x01 << 5;		//Receive Polarity Mode
	LPC_CAN1->MOD &=~ 0x01 << 7;		//Test Mode
}
/*
*@brief Write BusCan
*@param str_bus
*@param			uint32_t id_Bus;
				uint8_t dlc;
				uint8_t data[8];
*/
void Write_BusCan(str_bus *s){
	while((LPC_CAN1->GSR & 0x1 << 2) == 0); //check buffer libre

	LPC_CAN1->TFI1 = 0x01 << 31; 		//Id 29 bits FF = 1
	LPC_CAN1->TID1 = s->id_Bus;		//Identifier
	LPC_CAN1->TFI1 |= s->dlc << 16;		//Data Length Code

	LPC_CAN1->TDA1 = s->data[0];		//Datas
	LPC_CAN1->TDA1 |= s->data[1] << 8;
	LPC_CAN1->TDA1 |= s->data[2] << 16;
	LPC_CAN1->TDA1 |= s->data[3] << 24;
	LPC_CAN1->TDB1 = s->data[4];
	LPC_CAN1->TDB1 |= s->data[5] << 8;
	LPC_CAN1->TDB1 |= s->data[6] << 16;
	LPC_CAN1->TDB1 |= s->data[7] << 24;

	// check du buffer libre stat reg

	LPC_CAN1->CMR |= 1 << 5;					//Select buffer

	LPC_CAN1->CMR |= 0x01;						//Transmission
}

void Read_BusCan(){

}
