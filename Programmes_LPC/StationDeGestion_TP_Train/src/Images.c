#include "Images.h"

/**
 *@brief
 *@param image
 */
void Draw_Image(const tImage *image) {
	int size_array = (image->width * image->height) * 3;
	int i;
	for (i = 0; i < size_array; i += 3) {
		Write_pixel(image->data[i], image->data[i + 1], image->data[i + 2]);
	}
}
