/*
*@file ControlTrain.c
*@author Rafael Marques
*@version 1.0
*@date 10 mai 2014
*@brief Affect value of transmission
*/

#include "ControlTrain.h"

/*
*@brief StopGoTrain
*@param str_bus
*@param			uint32_t id_Bus
				uint8_t dlc
				uint8_t data[8]
*@param			int statu
*/
void StopGoTrain(str_bus* str,int statu){
	str->id_Bus = 0x00004711;
	str->dlc = 0x5;

	str->data[0] = 0;
	str->data[1] = 0;

	str->data[2] = 0;
	str->data[3] = 0;

	str->data[4] = statu;
}
/*
*@brief ChangeDirection
*@param str_bus
*@param			uint32_t id_Bus
				uint8_t dlc
				uint8_t data[8]
*@param			int NoTrain
*@param			int direction
*/
void ChangeDirection(str_bus* str,int NoTrain,int direction){
	str->id_Bus = 0x000A4711;
	str->dlc = 0x5;

	str->data[0] = 0;
	str->data[1] = 0;

	str->data[2] = NoTrain >> 8;
	str->data[3] = NoTrain & 255;

	str->data[4] = direction;
	str->data[5] = 0;

	str->data[6] = 0;
	str->data[7] = 0;
}
/*
*@brief ChangeSpeed
*@param str_bus
*@param			uint32_t id_Bus
				uint8_t dlc
				uint8_t data[8]
*@param			int NoTrain
*@param			int speed
*/
void ChangeSpeed(str_bus* str,int NoTrain,int speed){
	str->id_Bus = 0x00084711;
	str->dlc = 0x6;

	str->data[0] = 0;
	str->data[1] = 0;

	str->data[2] = NoTrain >> 8;
	str->data[3] = NoTrain & 255;

	str->data[4] = speed >> 8;
	str->data[5] = speed & 255;

	str->data[6] = 0;
	str->data[7] = 0;
}
/*
*@brief TurnLight
*@param str_bus
*@param			uint32_t id_Bus
				uint8_t dlc
				uint8_t data[8]
*@param			int NoTrain
*@param			int statu
*/
void TurnLight(str_bus* str,int statu){
	str->id_Bus = 0x000C4711;
	str->dlc = 0x5;

	str->data[0] = 0;
	str->data[1] = 0;

	str->data[2] = NoTrain >> 8;
	str->data[3] = NoTrain & 255;

	str->data[4] = statu;
	str->data[5] = 0;

	str->data[6] = 0;
	str->data[7] = 0;
}
