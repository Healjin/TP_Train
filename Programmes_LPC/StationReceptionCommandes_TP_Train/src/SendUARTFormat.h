/*
 * SendUARTFormat.h
 *
 *  Created on: 4 juin 2014
 *      Author: David
 */

#ifndef SENDUARTFORMAT_H_
#include "uart.h"
#include "stdbool.h"
#define SENDUARTFORMAT_H_

#define START_TRAIN "STATRAIN"
#define STOP_TRAIN "STOTRAIN"
#define CHANGE_SPEED "LxxVxxxx"
#define CHANGE_DIR "LxxSx"

void send_direction(uint8_t n_train, bool direction);
void send_speed(uint8_t n_train, uint16_t speed_train);
void send_lights(uint8_t n_train, bool state);


#endif /* SENDUARTFORMAT_H_ */
