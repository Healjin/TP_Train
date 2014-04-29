#include "ExtLab2.h"

static uint8_t save_data_bus_values = 0xFE;

/**
*@brief Select bus control on the ExtLab2
*@details Select the control bus on the ExtLab2 and restore the old
*@details state of this one ( with the variable save_data_bus_values).
*/
void Select_control_bus()
{
	/* -- Restore bus control -- */
	LPC_GPIO0->FIOMASK = ~ (0xFF << 4);
	LPC_GPIO0->FIOPIN = (save_data_bus_values << 4);
	LPC_GPIO0->FIOMASK = 0;
	/* -- Select control bus -- */
	LPC_GPIO0->FIOPIN &=~ (0x3 << 21);
	LPC_GPIO0->FIOPIN |= 0x3 << 21;
}

/**
*@brief Select the dispay bus on ExtLab2
*@details Once the display bus selected all datas will directly sent to
*@details the lcd screen
*/
void Select_display_bus()
{
	/* -- Select display control -- */
	LPC_GPIO0->FIOPIN &=~ (0x3 << 21);
	LPC_GPIO0->FIOPIN |= 0x2 << 21;
}

/**
*@brief Valide all datas put on the control bus
*@details Switch the state on p2.8 to launch to validate the datas, but we also save the
*@details datas (in case we switch to the display bus)
*/
void Valide_datas_bus_to_extlab2()
{
	save_data_bus_values = (LPC_GPIO0->FIOPIN >> 4) & 0xFF ;
	/* -- Validate all values set on P2 bus -- */
	LPC_GPIO2->FIOPIN |= 1 << 8;
	LPC_GPIO2->FIOPIN &=~ (1 << 8);
}
