/*
 * Images.h
 *
 *  Created on: 14 mars 2014
 *      Author: David
 */

#ifndef IMAGES_H_
#define IMAGES_H_

#include "LPC17xx.h"
#include <cr_section_macros.h>

#include "Ecran.h"

 typedef struct {
     const uint8_t *data;
     uint16_t width;
     uint16_t height;
 } tImage;

void Draw_Image(const tImage *image);
#endif /* IMAGES_H_ */
