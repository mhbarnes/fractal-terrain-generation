#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "color.h"

using namespace std;

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

double GetHue(RGB rgb)
{
	double min = Min(Min(rgb.red, rgb.green), rgb.blue);
	double max = Max(Max(rgb.red, rgb.green), rgb.blue);

	double hue = 0;

	if (rgb.red >= rgb.green && rgb.red >= rgb.blue)
		hue = (rgb.green - rgb.blue) / (max - min);
	else if (rgb.green >= rgb.red && rgb.green >= rgb.blue)
		hue = 2 + (rgb.blue - rgb.red) / (max - min);
	else if (rgb.blue >= rgb.red && rgb.blue >= rgb.green)
		hue = 4 + (rgb.red - rgb.green) / (max - min);

	if (hue < 0)
		hue += 360;

	return hue * 60;
}

double GetSaturation(RGB rgb)
{
	double max = Max(Max(rgb.red, rgb.green), rgb.blue);

	return (max == 0) ? 0 : 1 - (1 * Min(Min(rgb.red, rgb.green), rgb.blue) / max);
}

double GetValue(RGB rgb)
{
	return (double) Max(Max(rgb.red, rgb.green), rgb.blue) / 255;
}

HSV RGB2HSV(RGB rgb)
{
	HSV hsv;

	hsv.hue = GetHue(rgb);
	hsv.saturation = GetSaturation(rgb);
	hsv.value = GetValue(rgb);

	return hsv;
}

void RGB2HSV(struct RGB ** rgb_arr, struct HSV ** hsv_arr, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
			hsv_arr[i][j] = RGB2HSV(rgb_arr[i][j]);
}
