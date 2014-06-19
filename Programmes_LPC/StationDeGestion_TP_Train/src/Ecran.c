/**
 *@file Ecran.c
 *@author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 *@version 1.0
 *@date 19 June 2014
 *@briefs Contain functions to control the screen.
 */

#include "Ecran.h"

/**
 * Initialize all GPIO used with the screen.
 */
void Init_ports_display() {
	LPC_GPIO0->FIODIR |= 0x3 << 21; // Configure select (display) to output
	Select_control_bus(); // Enable control mode on P2

	LPC_GPIO2->FIODIR |= 1 << 8; // Set output for the bit that send the bus
	LPC_GPIO2->FIOCLR = 1 << 8; // Preset 0 to send the bus

	LPC_GPIO0->FIODIR |= 0xFF << 4; // Configure bus display to output (8bits)
	LPC_GPIO0->FIOPIN &= ~0x3 << 4; // Set write mode for display and disable display

	LPC_GPIO1->FIODIR |= 1 << DISPLAY_WRB; // Configuration output WRB
	LPC_GPIO1->FIODIR |= 1 << DISPLAY_CS; // Configuration output CS
	LPC_GPIO1->FIODIR |= 1 << DISPLAY_RS; // Configuration output RS

	Valide_datas_bus_to_extlab2(); // Update configuration
}
/**
 * Permit to choose on which index we want to write on the screen options.
 *@param idx Index address to access
 */
void Index_out(uint8_t idx) {
	/* -- Prepare index to be send -- */
	LPC_GPIO0->FIOMASK = ~(0xFF << 4); // Mask to write the index on the output
	LPC_GPIO0->FIOPIN = idx << 4; // Index to send to the display
	LPC_GPIO0->FIOMASK = 0; // Mask set to default

	/* -- Send index -- */
	LPC_GPIO1->FIOCLR = 1 << DISPLAY_RS; // Set 0 on RS
	LPC_GPIO1->FIOCLR = 1 << DISPLAY_CS; // Set 0 on CS
	LPC_GPIO1->FIOCLR = 1 << DISPLAY_WRB; // Set 0 on WRB
	LPC_GPIO1->FIOSET = 1 << DISPLAY_WRB; // Set 1 on WRB
	LPC_GPIO1->FIOSET = 1 << DISPLAY_CS; // Set 1 on CS
	LPC_GPIO1->FIOSET = 1 << DISPLAY_RS; // Set 1 on RS
}
/**
 * Permit to change parameters on the index selected with the function Index_out.
 *@param param Datas to write
 */
void Parameter_out(uint16_t param) {
	/* -- Prepare params to be send -- */
	LPC_GPIO0->FIOMASK = ~(0xFF << 4); // Mask to write the params on the output
	LPC_GPIO0->FIOPIN = (param >> 8) << 4; // Paramater to send to the display
	LPC_GPIO0->FIOMASK = 0; // Mask set to default

	/* -- Send param -- */
	LPC_GPIO1->FIOCLR = 1 << DISPLAY_CS; // Set 0 on CS
	LPC_GPIO1->FIOCLR = 1 << DISPLAY_WRB; // Set 0 on WRB
	LPC_GPIO1->FIOSET = 1 << DISPLAY_WRB; // Set 1 on WRB
	LPC_GPIO1->FIOSET = 1 << DISPLAY_CS; // Set 1 on CS

	/* -- Prepare params to be send -- */
	LPC_GPIO0->FIOMASK = ~(0xFF << 4); // Mask to write the params on the output
	LPC_GPIO0->FIOPIN = param << 4; // Paramater to send to the display
	LPC_GPIO0->FIOMASK = 0; // Mask set to default

	/* -- Send param -- */
	LPC_GPIO1->FIOCLR = 1 << DISPLAY_CS; // Set 0 on CS
	LPC_GPIO1->FIOCLR = 1 << DISPLAY_WRB; // Set 0 on WRB
	LPC_GPIO1->FIOSET = 1 << DISPLAY_WRB; // Set 1 on WRB
	LPC_GPIO1->FIOSET = 1 << DISPLAY_CS; // Set 1 on CS
}
/**
 * Set gamma of the screen. Set register value, to fix color on the screen
 */
void Set_gamma() {
	Index_out(0x70);
	Parameter_out(0x1F00);
	Index_out(0x71);
	Parameter_out(0x2380);
	Index_out(0x72);
	Parameter_out(0x2A80);
	Index_out(0x73);
	Parameter_out(0x1511);
	Index_out(0x74);
	Parameter_out(0x1C11);
	Index_out(0x75);
	Parameter_out(0x1B15);
	Index_out(0x76);
	Parameter_out(0x1A15);
	Index_out(0x77);
	Parameter_out(0x1C18);
	Index_out(0x78);
	Parameter_out(0x2115);
}

/**
 * Send a color to the touchscreen, this function need to be called 3 times to set all color on a pixel (R, G, B)
 *@param color Color sent
 */
void Send_color(uint8_t color) {
	/* -- Prepare color to be send -- */
	LPC_GPIO0->FIOMASK = ~(0xFF << 4); // Mask to write the color on the output
	LPC_GPIO0->FIOPIN = color << 4; // color to send to the display
	LPC_GPIO0->FIOMASK = 0; // Mask set to default

	/* -- Send color -- */
	LPC_GPIO1->FIOCLR = 1 << DISPLAY_CS; // Set 0 on CS
	LPC_GPIO1->FIOCLR = 1 << DISPLAY_WRB; // Set 0 on WRB
	LPC_GPIO1->FIOSET = 1 << DISPLAY_WRB; // Set 1 on WRB
	LPC_GPIO1->FIOSET = 1 << DISPLAY_CS; // Set 1 on CS
}
/**
 * Screen initialisation details Set configuration: 8bits,262k color,CPU interface,Standby OFF,Set Gamma,Display on
 */
void Init_display() {
	Init_ports_display();

	LPC_GPIO0->FIOPIN &= ~(1 << 4); // Disable display
	Valide_datas_bus_to_extlab2();

	Select_display_bus();

	/* -- 8bits mode -- */
	Index_out(0x24);

	/* -- CPU interface -- */
	Index_out(0x02);
	Parameter_out(0x0000);

	/* -- 262k color -- */
	Index_out(0x03);
	Parameter_out(0x4130);

	/* -- Standby OFF -- */
	Index_out(0x10);
	Parameter_out(0x0000);

	/* -- Set Gamma configuration -- */
	Set_gamma();

	/* -- Display on -- */
	Index_out(0x05);
	Parameter_out(0x0001);

	Select_control_bus();
	LPC_GPIO0->FIOPIN |= 1 << 4; // Enable display
	Valide_datas_bus_to_extlab2();
}
/**
 * Send RGB color on pixel
 *@param red value between 0 and 255
 *@param green value between 0 and 255
 *@param blue value between 0 and 255
 */
void Write_pixel(uint8_t red, uint8_t green, uint8_t blue) {
	/* Index to write a pixel on the screen */
	Index_out(0x22);
	/* -- Send colors to the display -- */
	Send_color(red);
	Send_color(green);
	Send_color(blue);
}

/**
 * Set cursor localisation
 *@param x value between 0 and 240
 *@param y value between 0 and 320
 */
void Set_cursor(uint16_t x, uint16_t y) {
	Index_out(0x20);
	Parameter_out(x);
	Index_out(0x21);
	Parameter_out(y);
}

/**
 * Creation of a window on the screen
 *@details create a window on the screen by precising a size
 *@param v_start largeur = v_start to v_end
 *@param v_end
 *@param h_start longueur = h_start to h_end
 *@param h_end
 */
void Create_partial_screen(uint16_t v_start, uint16_t v_end, uint8_t h_start, uint8_t h_end) {
	Index_out(0x35);
	Parameter_out(v_start);
	Index_out(0x36);
	Parameter_out(v_end);
	Index_out(0x37);
	Parameter_out((h_start << 8) | h_end);
}
