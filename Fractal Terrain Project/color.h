#ifndef COLOR_H
#define COLOR_H
#include <iostream>

using namespace std;

// RGB struct
struct RGB {
	int red;
	int green;
	int blue;
};

// HSV struct
struct HSV {
	double hue;
	double saturation;
	double value;
};

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
double GetSaturation(RGB rgb);
double GetValue(RGB rgb);

HSV RGB2HSV(RGB rgb);
void RGB2HSV(struct RGB ** rgb_arr, struct HSV ** hsv_arr, int rows, int cols);

#endif
