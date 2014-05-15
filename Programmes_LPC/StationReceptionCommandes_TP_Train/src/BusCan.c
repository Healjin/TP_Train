/*
*@file BusCan.c
*@author Swagteam
*@version 1.0
*@date 1 April 2014
*@brief BusCan configuration
*/
#include "BusCan.h"

void Init_BusCan(){

	LPC_SC->PCONP |= 0x1 << 13;			//Power
	LPC_SC->PCLKSEL0 &=~ 0x03 << 26;	//Peripheral clock

	LPC_SC->PCLKSEL0 &=~ 0x03 << 28;	//Peripheral clock

	LPC_CAN1->BTR |= 0x1110 << 16;		//TSEG1 = 14
	LPC_CAN1->BTR |= 0x011 << 20;		//TSEG2 = 3
	LPC_CAN1->BTR |= 5;					//BRP


	LPC_PINCON->PINSEL0 |= 0x01;		//RD1
	LPC_PINCON->PINSEL0 |= 0x01 << 2;	//TD1

	LPC_CAN1->MOD &=~ 0x01;  			//Reset Mode
	LPC_CAN1->MOD &= 0x01 << 1;			//Listen Only Mode
	LPC_CAN1->MOD &=~ 0x01 << 2;		//Self Test Mode
	LPC_CAN1->MOD &=~ 0x01 << 3;		//Transmit Priority Mode
	LPC_CAN1->MOD &=~ 0x01 << 4;		//Sleep Mode
	LPC_CAN1->MOD &=~ 0x01 << 5;		//Receive Polarity Mode
	LPC_CAN1->MOD &=~ 0x01 << 7;		//Test Mode
}
/*
void Write_BusCan(str_bus *s){

	LPC_CAN1->TFI1 |= 0x01 << 31; 		//Id 29 bits FF = 1
	LPC_CAN1->TID1 |= s->id_Bus;		//Identifier
	LPC_CAN1->TFI1 |= s->dlc << 16;		//Data Length Code
	LPC_CAN1->TDA1 |= s->data;			//Datas

	LPC_CAN1->CMR |= 0x01;				//Transmission
}*/
void Read_BusCan(){

}
