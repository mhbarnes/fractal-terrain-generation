#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "bitmap_image.hpp"

using namespace std;

// RGB struct
struct RGB {
	float red;
	float green;
	float blue;
};

// HSV struct
struct HSV {
	double hue;
	double saturation;
	double value;
};

RGB CreateRGB(int red, int green, int blue);

HSV CreateHSV(double hue, double saturation, double value);

RGB BitmapToRGB(rgb_t rgb_bmp);

HSV BitmapToHSV(rgb_t rgb_bmp);

rgb_t RGBToBitmap(int red, int green, int blue);
rgb_t RGBToBitmap(RGB rgb);

rgb_t HSVToBitmap(HSV hsv);

/******************************************************************************/

struct RGB ** init_RGB(int rows, int cols);
struct HSV ** init_HSV(int rows, int cols);

void populate_RGB(struct RGB ** rgb_arr, int rows, int cols);
void populate_HSV(struct HSV ** hsv_arr, int rows, int cols);

void print_RGB(struct RGB ** rgb_arr, int rows, int cols);
void print_HSV(struct HSV ** hsv_arr, int rows, int cols);

void delete_RGB(struct RGB ** rgb_arr, int rows, int cols);
void delete_HSV(struct HSV ** hsv_arr, int rows, int cols);

static double Min(double a, double b);
static double Max(double a, double b);

double GetHue(RGB rgb);
double GetHue(double red, double green, double blue);
double GetSaturation(RGB rgb);
double GetSaturation(double red, double green, double blue);
double GetValue(RGB rgb);
double GetValue(double red, double green, double blue);

HSV RGB2HSV(RGB rgb);
HSV RGB2HSV(double red, double green, double blue);
void RGB2HSV(struct RGB ** rgb_arr, struct HSV ** hsv_arr, int rows, int cols);

RGB HSV2RGB(HSV hsv);

#endif
