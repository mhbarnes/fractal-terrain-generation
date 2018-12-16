#include "color.h"

using namespace std;


RGB CreateRGB(int red, int green, int blue)
{
	RGB rgb;

	rgb.red = red;
	rgb.green = green;
	rgb.blue = blue;

	return rgb;
}

HSV CreateHSV(double hue, double saturation, double value)
{
	HSV hsv;

	hsv.hue = hue;
	hsv.saturation = saturation;
	hsv.value = value;

	return hsv;
}

RGB BitmapToRGB(rgb_t rgb_bmp)
{
	RGB rgb;

	rgb.red = rgb_bmp.red;
	rgb.green = rgb_bmp.green;
	rgb.blue = rgb_bmp.blue;

	return rgb;
}

HSV BitmapToHSV(rgb_t rgb_bmp)
{
	return RGB2HSV(BitmapToRGB(rgb_bmp));
}

rgb_t RGBToBitmap(int red, int green, int blue)
{
	return RGBToBitmap(CreateRGB(red, green, blue));
}
rgb_t RGBToBitmap(RGB rgb)
{
	rgb_t rgb_bmp;

	rgb_bmp.red = rgb.red;
	rgb_bmp.green = rgb.green;
	rgb_bmp.blue = rgb.blue;

	return rgb_bmp;
}

rgb_t HSVToBitmap(HSV hsv)
{
	return RGBToBitmap(HSV2RGB(hsv));
}

/******************************************************************************

int main(){
    int rows = 3;
    int cols = 3;
    
    struct RGB ** rgb_arr = init_RGB(rows, cols);
    struct HSV ** hsv_arr = init_HSV(rows, cols);

    populate_RGB(rgb_arr, rows, cols);
    populate_HSV(hsv_arr, rows, cols);
    
    RGB2HSV(rgb_arr, hsv_arr, rows, cols);
    
    print_RGB(rgb_arr, rows, cols);
    print_HSV(hsv_arr, rows, cols);
    
    delete_RGB(rgb_arr, rows, cols);
    delete_HSV(hsv_arr, rows, cols);
}

/******************************************************************************/

struct RGB ** init_RGB(int rows, int cols){
	struct RGB ** rgb_arr;
	rgb_arr = new struct RGB * [rows];
	for(int i = 0; i < rows; i++){
		rgb_arr[i] = new struct RGB [cols];	
	}
	return rgb_arr;
}

struct HSV ** init_HSV(int rows, int cols){
	struct HSV ** hsv_arr;
	hsv_arr = new struct HSV * [rows];
	for(int i = 0; i < rows; i++){
		hsv_arr[i] = new struct HSV [cols];	
	}
	return hsv_arr;
}

/******************************************************************************/

void populate_RGB(struct RGB ** rgb_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			rgb_arr[i][j].red = rand() % 256 + 1;
            rgb_arr[i][j].green = rand() % 256 + 1;
            rgb_arr[i][j].blue = rand() % 256 + 1;	
		}	
	}
}

void populate_HSV(struct HSV ** hsv_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			hsv_arr[i][j].hue = 0;
            hsv_arr[i][j].saturation = 0;
            hsv_arr[i][j].value = 0;	
		}	
	}
}

/******************************************************************************/

void print_RGB(struct RGB ** rgb_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
        cout << endl;
		for(int j = 0; j < cols; j++){
			cout << " R: " << rgb_arr[i][j].red << " | ";
		}	
        cout << endl;
        for(int j = 0; j < cols; j++){
            cout << " G: " << rgb_arr[i][j].green << " | ";
		}
        cout << endl;
        for(int j = 0; j < cols; j++){
            cout << " B: " << rgb_arr[i][j].blue << " | ";	
		}
        cout << endl;
    }
}

void print_HSV(struct HSV ** hsv_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
        cout << endl;
		for(int j = 0; j < cols; j++){
			cout << " H: " << hsv_arr[i][j].hue << " | ";
		}	
        cout << endl;
        for(int j = 0; j < cols; j++){
            cout << " S: " << hsv_arr[i][j].saturation << " | ";
        }	
        cout << endl;
        for(int j = 0; j < cols; j++){
            cout << " V: " << hsv_arr[i][j].value << " | ";	
        }	
        cout << endl;
	}
}

/******************************************************************************/

void delete_RGB(struct RGB ** rgb_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		delete [] rgb_arr[i];	
	}
	delete [] rgb_arr;
}

void delete_HSV(struct HSV ** hsv_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		delete [] hsv_arr[i];	
	}
	delete [] hsv_arr;
}

/******************************************************************************/

static double Min(double a, double b) {
	return a <= b ? a : b;
}

static double Max(double a, double b) {
	return a >= b ? a : b;
}

double GetHue(double red, double green, double blue)
{
	double min = Min(Min(red, green), blue);
	double max = Max(Max(red, green), blue);

	double hue = 0;

	if (red >= green && red >= blue)
		hue = (green - blue) / (max - min);
	else if (green >= red && green >= blue)
		hue = 2 + (blue - red) / (max - min);
	else if (blue >= red && blue >= green)
		hue = 4 + (red - green) / (max - min);

	if (hue < 0)
		hue += 360;

	return hue * 60;
}
double GetHue(RGB rgb)
{
	return GetHue(rgb.red, rgb.green, rgb.blue);
}

double GetSaturation(double red, double green, double blue)
{
	double max = Max(Max(red, green), blue);

	return (max == 0) ? 0 : 1 - (1 * Min(Min(red, green), blue) / max);
}
double GetSaturation(RGB rgb)
{
	double max = Max(Max(rgb.red, rgb.green), rgb.blue);

	return GetSaturation(rgb.red, rgb.green, rgb.blue);
}

double GetValue(double red, double green, double blue)
{
	return (double)Max(Max(red, green), blue) / 255;
}
double GetValue(RGB rgb)
{
	return GetValue(rgb.red, rgb.green, rgb.blue);
}

HSV RGB2HSV(RGB rgb)
{
	HSV hsv;

	hsv.hue = GetHue(rgb);
	hsv.saturation = GetSaturation(rgb);
	hsv.value = GetValue(rgb);

	return hsv;
}
HSV RGB2HSV(double red, double green, double blue)
{
	HSV hsv;

	hsv.hue = GetHue(red, green, blue);
	hsv.saturation = GetSaturation(red, green, blue);
	hsv.value = GetValue(red, green, blue);

	return hsv;
}

void RGB2HSV(struct RGB ** rgb_arr, struct HSV ** hsv_arr, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
			hsv_arr[i][j] = RGB2HSV(rgb_arr[i][j]);
}

RGB HSV2RGB(HSV hsv)
{
	int hi = (int) floor(hsv.hue / 60) % 6;
	double f = hsv.hue / 60 - floor(hsv.hue / 60);

	double value = hsv.value * 255;
	int v = value;
	int p = value * (1 - hsv.saturation);
	int q = value * (1 - f * hsv.saturation);
	int t = value * (1 - (1 - f) * hsv.saturation);

	if (hi == 0)
		return CreateRGB(v, t, p);
	if (hi == 1)
		return CreateRGB(q, v, p);
	if (hi == 2)
		return CreateRGB(p, v, t);
	if (hi == 3)
		return CreateRGB(p, q, v);
	if (hi == 4)
		return CreateRGB(t, p, v);

	return CreateRGB(v, p, q);
}
int RandInt(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

double RandDouble(double min, double max)
{
	return ((double) rand() / RAND_MAX) * (max - min) + min;
}

RGB RandColorRGB()
{
	return CreateRGB(RandInt(0, 255), RandInt(0, 255), RandInt(0, 255));
}

HSV RandColorHSV()
{
	return CreateHSV(RandDouble(0, 360), RandDouble(0, 1), RandDouble(0, 1));
}