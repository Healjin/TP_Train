/*
 *@file drawScreen.c
 *@author Da Silva Andrade David, Antoine Berger, Dos Santos Rafael
 *@version 1.0
 *@date 19 June 2014
 *@briefs Contain functions to draws things on the screen.
 */

#include "drawScreen.h"

/**
 *@brief Change a color in a zone
 *@param x_start Where start x in the screen
 *@param x_stop Where stop x in the screen
 *@param y_start Where start y in the screen
 *@param y_stop Where stop y in the screen
 *@param color_characted Which color the zone is changed [Red, Green, Blue]
 */
void change_zone_color(uint16_t x_start, uint16_t x_stop, uint16_t y_start, uint16_t y_stop, uint8_t *color_character) {
	Select_display_bus();
	Create_partial_screen(y_start, y_stop, x_start, x_stop);
	Set_cursor(x_start, y_start);
	uint16_t var;
	uint32_t nb_pixels = (x_stop - x_start + 1) * (y_stop - y_start + 1);
	for (var = 0; var < nb_pixels; var++)
		Write_pixel(color_character[0], color_character[1], color_character[2]);
}

/**
 *@brief Draw an arrow to the right
 *@param x_start Where the arrow base start on x
 *@param y_start Where the arrow base start on y
 *@param thickness Thickness of the arrow
 *@param height_arrow Arrow's height
 *@param color Arrow color [Red, Green, Blue]
 */
void draw_arrow_right(uint16_t x_start, uint16_t y_start, uint8_t thickness, uint8_t height_arrow, uint8_t length,
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
		for (i = 0; i < height_arrow; i++) {
			Set_cursor(x_start + length - i - j + (thickness - 1), y_start + i);
			Write_pixel(color[0], color[1], color[2]);
			Set_cursor(x_start + length - i - j + (thickness - 1), y_start - i);
			Write_pixel(color[0], color[1], color[2]);
		}
	}
}

/**
 *@brief Draw an arrow to the left
 *@param x_start Where the arrow tip start on x
 *@param y_start Where the arrow tip start on y
 *@param thickness Thickness of the arrow
 *@param height_arrow Arrow's height
 *@param color Arrow color [Red, Green, Blue]
 */
void draw_arrow_left(uint16_t x_start, uint16_t y_start, uint8_t thickness, uint8_t height_arrow, uint8_t length,
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
		for (i = 0; i < height_arrow; i++) {
			Set_cursor(x_start + i + j, y_start + i);
			Write_pixel(color[0], color[1], color[2]);
			Set_cursor(x_start + i + j, y_start - i);
			Write_pixel(color[0], color[1], color[2]);
		}
	}
}

/**
 *@brief Draw 6 sunbeams around the lamp to show the lights on
 *@param color Sunbeams color [Red, Green, Blue]
 *@param length Length of the sunbeams
 */
void display_lights(uint8_t *color, uint8_t length)
{
	int i;
	Set_cursor(110-length, 283);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(110-length, 284);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(110-length, 288);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(110-length, 289);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(110-length, 292);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(110-length, 293);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(131, 283);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(131, 284);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(131, 288);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(131, 289);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(131, 292);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
	Set_cursor(131, 293);
	for (i = 0; i < length; i++)
		Write_pixel(color[0], color[1], color[2]);
}
