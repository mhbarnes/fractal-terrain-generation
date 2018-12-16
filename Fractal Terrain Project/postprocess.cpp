#include "postprocess.h"

bitmap_image sharpen(&bitmap_image bmp) {
	
}

bitmap_image box_blur(&bitmap_image bmp) {
	const float blurSizeH = 1.0 / 300.0;
	const float blurSizeV = 1.0 / 200.0;

	vec4 sum = vec4(0.0);
	for (int x = -4; x <= 4; x++)
		for (int y = -4; y <= 4; y++)
			sum += texture( texFramebuffer, vec2(Texcoord.x + x * blurSizeH, Texcoord.y + y * blurSizeV)) / 81.0;
	outColor = sum;
}

bitmap_image gauss_blur(&bitmap_image bmp) {
	int m = 3; //height and width of kernel

	rgt_t currPix;
	RGB kern [m][m];

	for (int i = 0; i < bmp.width(); i++) {
		for (int j = 0; j < bmp.height(); j++) {
			currPix = get_pixel[i][j];
			//

		}
	}

	HSV hsv = RGB2HSV((double) main.get_pixel(x, y).red, (double) main.get_pixel(x, y).red, (double) main.get_pixel(x, y).red);
}