/**
*@file ControlTrain.h
*@author Swagteam
*@version 1.0
*@date 20 may 2014
*@brief content constants and header of functions used on BusCan.h
*/

#ifndef ControlTrain_h_
#define ControlTrain_h_

#include "LPC17xx.h"
#include "BusCan.h"
str_bus str;
#define FORWARD_TRAIN 1
#define BACK_TRAIN 2

void StopGoTrain(str_bus* str,int statu);
void ChangeSpeed(str_bus *str,int NoTrain,int speed);
void ChangeDirection(str_bus* str,int NoTrain,int direction);
void SwitchSelect(uint8_t NoSwitch,uint8_t position);
void TurnLight(str_bus* str,int NoTrain,int statu);


#endif /* ControlTrain_h_ */
