/**
*@file uart.h
*@author Swagteam
*@version 1.0
*@date 25 march 2014
*@brief
*/
#ifndef UART0_INIT_H
#define UART0_INIT_H

#include <stdint.h>

void uart0_init(uint32_t baudrate);
void uart0_send(uint8_t *data, uint32_t length);

#endif
