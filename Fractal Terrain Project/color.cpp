#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "color.h"

using namespace std;

/******************************************************************************/

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

static int Min(int a, int b) {
	return a <= b ? a : b;
}

static int Max(int a, int b) {
	return a >= b ? a : b;
}

void RGB2HSV(struct RGB ** rgb_arr, struct HSV ** hsv_arr, int rows, int cols){
    double delta, min;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            min = Min(Min(rgb_arr[i][j].red, rgb_arr[i][j].green), rgb_arr[i][j].blue);
            hsv_arr[i][j].value = Max(Max(rgb_arr[i][j].red, rgb_arr[i][j].green), rgb_arr[i][j].blue);
            delta = hsv_arr[i][j].value - min;
            
            if(hsv_arr[i][j].value == 0.0){
               hsv_arr[i][j].saturation = 0;
            }
            else{
               hsv_arr[i][j].saturation = delta / hsv_arr[i][j].value;
            }
            
            if(hsv_arr[i][j].saturation == 0){
                hsv_arr[i][j].hue = 0.0;
            }
            else{
                if(rgb_arr[i][j].red == hsv_arr[i][j].value){
                    hsv_arr[i][j].hue = (rgb_arr[i][j].green - rgb_arr[i][j].blue) / delta;
                }
                else if(rgb_arr[i][j].green == hsv_arr[i][j].value){
                    hsv_arr[i][j].hue = 2 + (rgb_arr[i][j].blue - rgb_arr[i][j].red) / delta;
                }
                else if(rgb_arr[i][j].blue == hsv_arr[i][j].value){
                    hsv_arr[i][j].hue = 4 + (rgb_arr[i][j].red - rgb_arr[i][j].green) / delta;
                }
                hsv_arr[i][j].hue *= 60;
                
                if(hsv_arr[i][j].hue < 0.0){
                    hsv_arr[i][j].hue = hsv_arr[i][j].hue + 360;
                }
            }
            
           hsv_arr[i][j].value = hsv_arr[i][j].value/ 255;
        }
    }
}
