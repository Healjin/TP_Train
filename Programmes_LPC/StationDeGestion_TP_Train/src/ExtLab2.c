/**
 *@file ExtLab2.c
 *@author Swagteam
 *@version 1.0
 *@date June 2014
 *@brief Contain functions to control the ExtLab2 card
 */
#include "ExtLab2.h"

/* Contain the saving configuration on the bits of control */
static uint8_t save_data_bus_values = 0xFE;

/**
 *@brief Select bus control on the ExtLab2
 *@details Select the control bus on the ExtLab2 and restore the old
 *@details state of this one ( with the variable save_data_bus_values).
 */
void Init_Extlab2() {
	LPC_GPIO0->FIODIR |= 0x3 << 21;
	LPC_GPIO2->FIODIR |= 1 << 8;
	LPC_GPIO2->FIODIR |= 0b111 << 11;
}

/**
 *@brief Select bus control on the ExtLab2
 *@details Select the control bus on the ExtLab2 and restore the old
 *@details state of this one ( with the variable save_data_bus_values).
 */
void Select_control_bus() {
	/* -- Restore bus control -- */
	LPC_GPIO0->FIOMASK = ~(0xFF << 4);
	LPC_GPIO0->FIOPIN = (save_data_bus_values << 4);
	LPC_GPIO0->FIOMASK = 0;
	/* -- Select control bus -- */
	LPC_GPIO0->FIOPIN &= ~(0x3 << 21);
	LPC_GPIO0->FIOPIN |= 0x3 << 21;
}

/**
 *@brief Select the dispay bus on ExtLab2
 *@details Once the display bus selected all datas will directly sent to
 *@details the lcd screen
 */
void Select_display_bus() {
	/* -- Select display control -- */
	LPC_GPIO0->FIOPIN &= ~(0x3 << 21);
	LPC_GPIO0->FIOPIN |= 0x2 << 21;
}

/**
 *@brief Valide all datas put on the control bus
 *@details Switch the state on p2.8 to launch to validate the datas, but we also save the
 *@details datas (in case we switch to the display bus)
 */
void Valide_datas_bus_to_extlab2() {
	save_data_bus_values = (LPC_GPIO0->FIOPIN >> 4) & 0xFF;
	/* -- Validate all values set on P2 bus -- */
	LPC_GPIO2->FIOPIN |= 1 << 8;
	LPC_GPIO2->FIOPIN &= ~(1 << 8);
}

/**
 *@brief Initialization to use the rotate button
 *@details Active an interruption on the rotation of the button and
 *@details configure the GPIO to use the rotate button
 */
void Init_Rotate_button() {
	LPC_GPIO2->FIODIR |= 0b111 << 11; // Put output on select rotate button
	LPC_GPIO2->FIOCLR = 1 << 13;
	LPC_GPIO2->FIOSET = 0b11 << 11;

	NVIC_ClearPendingIRQ(EINT3_IRQn);
	LPC_GPIOINT->IO2IntEnR = 1 << 6;
	LPC_GPIOINT->IO2IntClr = 1 << 6;
	NVIC_EnableIRQ(EINT3_IRQn);
}
