/**
*@file uart.c
*@author Swagteam
*@version 1.0
*@date 27 march 2014
*@brief
*/
#include "LPC17xx.h"
#include "uart.h"

/******************************************************************
* Description:    Initialize UART port, setup pin select,
*                 clock, parity, stop bits, FIFO, etc.
*
* Parameter:      UART baudrate [bit/s]
*******************************************************************/
void uart0_init(uint32_t baudrate)
{
  uint32_t Fdiv;
  uint32_t pclkdiv, pclk;

  LPC_PINCON->PINSEL0 &= ~0x000000F0;
  LPC_PINCON->PINSEL0 |= 0x00000050;  /* RxD0 is P0.3 and TxD0 is P0.2 */
  /* By default, the PCLKSELx value is zero, thus, the PCLK for
  all the peripherals is 1/4 of the SystemFrequency. */
  /* Bit 6~7 is for UART0 */
  pclkdiv = (LPC_SC->PCLKSEL0 >> 6) & 0x03;
  switch ( pclkdiv )
  {
    case 0x00:
    default:
      pclk = SystemCoreClock/4;
      break;
    case 0x01:
      pclk = SystemCoreClock;
      break;
    case 0x02:
      pclk = SystemCoreClock/2;
      break;
    case 0x03:
      pclk = SystemCoreClock/8;
      break;
  }

  LPC_UART0->LCR = 0x83;            /* 8 bits, no Parity, 1 Stop bit */
  Fdiv = ( pclk / 16 ) / baudrate ; /* setup baud rate */
  LPC_UART0->DLM = Fdiv / 256;
  LPC_UART0->DLL = Fdiv % 256;
  LPC_UART0->LCR = 0x03;            /* DLAB = 0 */
  LPC_UART0->FCR = 0x07;            /* Enable and reset TX and RX FIFO. */
}


/*********************************************************
 * Description : 	Envoi de données sur l'UART 0
 *
 * data: 			Pointeur sur les données à envoyer
 * length: 			Nombre d'octets à envoyer
 ********************************************************/
void uart0_send(char *data, uint32_t length)
{
	int var;
	for (var = 0; var < length; var++) {
		while (!(LPC_UART0->LSR & 0x1 << 5));
		LPC_UART0->THR = data[var];
	}
}


uint32_t uart0_read(char *data, uint32_t length)
{
	uint32_t var;
	for (var = 0; var < length; var++) {
		// Read Rx buffer while we have data in input
		if ((LPC_UART0->LSR & 0x1) == 1)
			data[var] =LPC_UART0->RBR;
		else
			break;
	}
	return var;
}

uint32_t uart0_read_one_char(char *ch)
{
	if ( LPC_UART0->LSR & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
	{
		/* Clear errors */
		ch[0] = LPC_UART0->LSR;
		ch[0] = LPC_UART0->RBR;
		return 0;
	}
	if ( LPC_UART0->LSR & LSR_RDR )       /* Receive Data Ready */
	{
		ch[0] = LPC_UART0->RBR;
		return 1;
	}
	return 0;
}
