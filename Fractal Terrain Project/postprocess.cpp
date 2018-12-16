#include "postprocess.h"

bitmap_image sharpen(&bitmap_image bmp) {
	
}

bitmap_image box_blur(&bitmap_image bmp) {
	/*const float blurSizeH = 1.0 / 300.0;
	const float blurSizeV = 1.0 / 200.0;

	vec4 sum = vec4(0.0);
	for (int x = -4; x <= 4; x++)
		for (int y = -4; y <= 4; y++)
			sum += texture( texFramebuffer, vec2(Texcoord.x + x * blurSizeH, Texcoord.y + y * blurSizeV)) / 81.0;
	outColor = sum;*/
}

bitmap_image gauss_blur(&bitmap_image bmp) {
	int n = 3; //height and width of kernel, should be odd

	rgt_t currPix;
	RGB kern [n][n];

	for (int i = 0; i < bmp.width(); i++) {
		for (int j = 0; j < bmp.height(); j++) {
			currPix = get_pixel[i][j];
<<<<<<< HEAD
			for (int k = 0; k < n * n; k++) {
				
			}
=======
			
>>>>>>> 6710018993e5cc268541c3b2f06c4ed261c7a156
		}
	}

	HSV hsv = RGB2HSV((double) main.get_pixel(x, y).red, (double) main.get_pixel(x, y).red, (double) main.get_pixel(x, y).red);
}

//gauss_blur() helper functions (for boundary cases)
<<<<<<< HEAD
void pop_kern(RGB kern[][3], &bitmap_image bmp) {
	if ()
}
=======
>>>>>>> 6710018993e5cc268541c3b2f06c4ed261c7a156
void top_left(RGB kern[][3], &bitmap_image bmp) {
	kern[0][0] = kern[1][1];
	kern[0][1] = kern[1][1];
	kern[1][0] = kern[1][1];

	kern[0][2] = kern[1][2];
	kern[2][0] = kern[2][1];
}
void top_right(RGB kern[][3], &bitmap_image bmp) {
	kern[1][0] = kern[1][1];
	kern[2][0] = kern[1][1];
	kern[2][1] = kern[1][1];

	kern[0][0] = kern[0][1];
	kern[2][2] = kern[1][2];
}
void bot_left(RGB kern[][3], &bitmap_image bmp) {
	kern[0][1] = kern[1][1];
	kern[0][2] = kern[1][1];
	kern[1][2] = kern[1][1];

	kern[0][0] = kern[1][0];
	kern[2][2] = kern[2][1];
}
void bot_right(RGB kern[][3], &bitmap_image bmp) {
	kern[2][1] = kern[1][1];
	kern[2][2] = kern[1][1];
	kern[1][2] = kern[1][1];

	kern[2][0] = kern[1][0];
	kern[0][2] = kern[0][1];
}
void top_edge(RGB kern[][3], &bitmap_image bmp) {
	kern[0][0] = kern[0][1];
	kern[1][0] = kern[1][1];
	kern[2][0] = kern[2][1];
}
void left_edge(RGB kern[][3], &bitmap_image bmp) {
	kern[0][0] = kern[1][0];
	kern[0][1] = kern[1][1];
	kern[0][2] = kern[1][2];
}
void right_edge(RGB kern[][3], &bitmap_image bmp) {
	kern[2][0] = kern[1][0];
	kern[2][1] = kern[1][1];
	kern[2][2] = kern[1][2];
}
void bot_edge(RGB kern[][3], &bitmap_image bmp) {
	kern[0][2] = kern[1][0];
	kern[1][2] = kern[1][1];
	kern[2][2] = kern[1][2];
}