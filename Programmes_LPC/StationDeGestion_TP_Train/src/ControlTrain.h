/*
 * ControlTrain.h
 *
 *  Created on: 4 juin 2014
 *      Author: David
 */

#ifndef CONTROLTRAIN_H_
#include "uart.h"
#include "stdbool.h"
#define CONTROLTRAIN_H_



void send_direction(uint8_t n_train, bool direction);
void send_speed(uint8_t n_train, uint16_t speed_train);


#endif /* CONTROLTRAIN_H_ */
