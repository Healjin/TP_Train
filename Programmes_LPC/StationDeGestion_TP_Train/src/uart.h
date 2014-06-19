/**
 * @file uart.h
 * @author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 * @version 1.0
 * @date 19 June 2014
 * @brief Contain all functions to initialize, write and read on UART 0 and 3
 */
#ifndef UART0_INIT_H
#define UART0_INIT_H

#include <stdint.h>

#define LSR_RDR         0x01
#define LSR_OE          0x02
#define LSR_PE          0x04
#define LSR_FE          0x08
#define LSR_BI          0x10
#define LSR_THRE        0x20
#define LSR_TEMT        0x40
#define LSR_RXFE        0x80

void uart0_init(uint32_t baudrate);
void uart0_send(char *data, uint32_t length);
uint32_t uart0_read(char *data, uint32_t length);
uint32_t uart0_read_one_char(char *ch);
void uart3_init(uint32_t baudrate);
void uart3_send(char *data, uint32_t length);
uint32_t uart3_read(char *data, uint32_t length);
uint32_t uart3_read_one_char(char *ch);

#endif
