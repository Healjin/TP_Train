#include "Ecran.h"

/**
 *@brief
 *@details
 *@param
 *@param
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
 *@brief
 *@details
 *@param
 *@param
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
 *@brief
 *@details
 *@param
 *@param
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
 *@brief Set gamma of the screen
 *@details Set register value, to fix color on th screen
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
 *@brief set a color
 *@param color color sent
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
 *@brief Screen initialisation
 *@details Set configuration: 8bits,262k color,CPU interface,Standby OFF,Set Gamma,Display on
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
 *@brief send RGB color on pixel
 *@param red value between 0 and 255
 *@param green value between 0 and 255
 *@param blue value between 0 and 255
 */
void Write_pixel(uint8_t red, uint8_t green, uint8_t blue) {
	Index_out(0x22);
	/* -- Send colors to the display -- */
	Send_color(red);
	Send_color(green);
	Send_color(blue);
}

/**
 *@brief Set cursor localisation
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
 *@brief creation of a window on the screen
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

void change_zone_color(uint16_t x_start, uint16_t x_stop, uint16_t y_start, uint16_t y_stop, uint8_t *color_character) {
	Select_display_bus();
	Create_partial_screen(y_start, y_stop, x_start, x_stop);
	Set_cursor(x_start, y_start);
	uint16_t var;
	uint32_t nb_pixels = (x_stop - x_start + 1) * (y_stop - y_start + 1);
	for (var = 0; var < nb_pixels; var++)
		Write_pixel(color_character[0], color_character[1], color_character[2]);
}

void draw_arrow_right(uint16_t x_start, uint16_t y_start, uint8_t thickness, uint8_t heigth_arrow, uint8_t length,
		uint8_t *color) {

	/* PartialScreen to draw the line */
	Create_partial_screen(y_start - thickness / 2, y_start + thickness / 2, x_start, x_start + length - 1);
	Set_cursor(x_start, y_start - thickness / 2);

	int i;
	for (i = 0; i < length * thickness; i++) {
		Write_pixel(color[0], color[1], color[2]);
	}

	/* Restore partial screen */
	Create_partial_screen(0, 319, 0, 239);

	/* Draw the tip */
	int j;
	for (j = 0; j < thickness; j++) {
		for (i = 0; i < heigth_arrow; i++) {
			Set_cursor(x_start + length - i - j + (thickness - 1), y_start + i);
			Write_pixel(color[0], color[1], color[2]);
			Set_cursor(x_start + length - i - j + (thickness - 1), y_start - i);
			Write_pixel(color[0], color[1], color[2]);
		}
	}
}

void draw_arrow_left(uint16_t x_start, uint16_t y_start, uint8_t thickness, uint8_t heigth_arrow, uint8_t length,
		uint8_t *color) {

	/* PartialScreen to draw the line */
	Create_partial_screen(y_start - thickness / 2, y_start + thickness / 2, x_start + thickness - 1, x_start + length - 1 + thickness - 1);
	Set_cursor(x_start + thickness - 1, y_start - thickness / 2);

	int i;
	for (i = 0; i < length * thickness; i++) {
		Write_pixel(color[0], color[1], color[2]);
	}

	/* Restore partial screen */
	Create_partial_screen(0, 319, 0, 239);

	/* Draw the tip */
	int j;
	for (j = 0; j < thickness; j++) {
		for (i = 0; i < heigth_arrow; i++) {
			Set_cursor(x_start + i + j, y_start + i);
			Write_pixel(color[0], color[1], color[2]);
			Set_cursor(x_start + i + j, y_start - i);
			Write_pixel(color[0], color[1], color[2]);
		}
	}
}
