#include "noise.h"

bitmap_image simplex_noise(&bitmap_image bmp) {
	SimplexNoise simpNoise; //C++ simplex noise class

	float x = bmp.width; //width of bitmap
	float y = bmp.height; //height of bitmap
	float n; //noise value
	
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			n = simpNoise.noise(i,j); //uses function from c++ simplex noise header file, returns noise value
			bmp.rbg_t.red = n * bmp.rgb_t.red;
			bmp.rbg_t.green = n * bmp.rgb_t.green;
			bmp.rbg_t.blue = n * bmp.rgb_t.blue;
		}
	}
	return bmp;
}