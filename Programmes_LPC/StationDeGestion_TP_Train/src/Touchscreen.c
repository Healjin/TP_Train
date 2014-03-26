/*
 * Touchscreen.c
 *
 *  Created on: 15 mars 2014
 *      Author: David
 */
#include "Touchscreen.h"

void Init_touchscreen()
{
	/* -- Test pressing on touchscreen, init interrupt -- */
	/*LPC_GPIO2->FIODIR |= 0b111 << 11; // Bit for select input
	LPC_GPIO2->FIOCLR = 0b111 << 11;
	LPC_GPIO2->FIOSET = 0b101 << 11;
	LPC_GPIO2->FIODIR &=~ (1 << IRQ_Touchscreen);*/

	NVIC_EnableIRQ(EINT3_IRQn);
	LPC_GPIOINT->IO2IntEnF |= 1 << ExtLab2_IRQ;


	/* -- SPI for touchscreen -- */
	Select_control_bus();
	LPC_GPIO0->FIODIR |= 1 << CS_touchscreen;
	LPC_GPIO0->FIOSET = 1 << CS_touchscreen; // Release (/CS) touchscreen
	Valide_datas_bus_to_extlab2();
	LPC_PINCON->PINSEL0 |= 0x3 << 30; // SCK select
	LPC_PINCON->PINSEL1 |= 0xF << 2; // Select MOSI and MISO
}

uint16_t Read_x_12bits()
{
	LPC_GPIO0->FIOCLR = 1 << CS_touchscreen; // Select (/CS) touchscreen
	Valide_datas_bus_to_extlab2();

	/* Read x with ADC off and PENIRQ enabled */
	Write_only_SPI_8bits(0xD2);
	uint8_t x_msb = Write_Read_SPI_8bits(0x00);
	uint8_t x_lsb = Write_Read_SPI_8bits(0x00);

	/* Convert data frame to x on 12 bits */
	uint16_t x = x_lsb >> 3;
	x |= ((x_msb &~ 0x80) << 5);

	LPC_GPIO0->FIOSET = 1 << CS_touchscreen; // Release (/CS) touchscreen
	Valide_datas_bus_to_extlab2();

	return x;
}

uint16_t Read_y_12bits()
{
	LPC_GPIO0->FIOCLR = 1 << CS_touchscreen; // Select (/CS) touchscreen
	Valide_datas_bus_to_extlab2();

	/* Read y with ADC off and PENIRQ enabled */
	Write_only_SPI_8bits(0x92);
	uint8_t y_msb = Write_Read_SPI_8bits(0x00);
	uint8_t y_lsb = Write_Read_SPI_8bits(0x00);

	/* Convert data frame to y on 12 bits */
	uint16_t y = y_lsb >> 3;
	y |= ((y_msb &~ 0x80) << 5);

	LPC_GPIO0->FIOSET = 1 << CS_touchscreen; // Release (/CS) touchscreen
	Valide_datas_bus_to_extlab2();

	return y;
}

void Read_x_and_y_12bits(uint16_t* x, uint16_t* y)
{
	LPC_GPIO0->FIOCLR = 1 << CS_touchscreen; // Select (/CS) touchscreen
	Valide_datas_bus_to_extlab2();

	/* Read y with ADC on and PENIRQ disabled */
	Write_only_SPI_8bits(0xD3);					// Options
	uint8_t x_msb = Write_Read_SPI_8bits(0x00);
	uint8_t x_lsb = Write_Read_SPI_8bits(0x00);

	/* Convert data frame to x on 12 bits */
	*x = x_lsb >> 3;
	*x |= ((x_msb &~ 0x80) << 5);

	/* Read y with ADC off and PENIRQ enabled */
	Write_only_SPI_8bits(0x92);					// Options
	uint8_t y_msb = Write_Read_SPI_8bits(0x00);
	uint8_t y_lsb = Write_Read_SPI_8bits(0x00);

	/* Convert data frame to y on 12 bits */
	*y = y_lsb >> 3;
	*y |= ((y_msb &~ 0x80) << 5);

	LPC_GPIO0->FIOSET = 1 << CS_touchscreen; // Release (/CS) touchscreen
	Valide_datas_bus_to_extlab2();
}
