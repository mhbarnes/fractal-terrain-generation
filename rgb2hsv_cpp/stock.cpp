#include <iostream>
#include <cstdlib>
#include "color.h"
#include <algorithm>

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

int main(){
    int rows = 3;
    int cols = 3;
    
    struct RGB ** rgb_arr = init_RGB(rows, cols);
    struct HSV ** hsv_arr = init_HSV(rows, cols);

    populate_RGB(rgb_arr, rows, cols);
    populate_HSV(rgb_arr, hsv_arr, rows, cols);
        
    cout << endl;
    
    print_RGB(rgb_arr, rows, cols);
    print_HSV(hsv_arr, rows, cols);
    
    delete_RGB(rgb_arr, rows, cols);
    delete_HSV(hsv_arr, rows, cols);   
    
    return 0;
}

/* THE FUNCTIONS BELOW ARE DEDICATED TO THE RGB STRUCT*/

struct RGB ** init_RGB(int rows, int cols){
	struct RGB ** rgb_arr;
	rgb_arr = new struct RGB * [rows];
	for(int i = 0; i < rows; i++){
		rgb_arr[i] = new struct RGB [cols];	
	}
	return rgb_arr;
}

void populate_RGB(struct RGB ** rgb_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			rgb_arr[i][j].red = rand() % 256 + 1;
            rgb_arr[i][j].green = rand() % 256 + 1;
            rgb_arr[i][j].blue = rand() % 256 + 1;	
		}	
	}
}

void print_RGB(struct RGB ** rgb_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			cout << rgb_arr[i][j].red << "|" << rgb_arr[i][j].green <<"|"<< rgb_arr[i][j].blue << " ";	
		}	
		cout << endl;
	}
}

void delete_RGB(struct RGB ** rgb_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		delete [] rgb_arr[i];	
	}
	delete [] rgb_arr;
}

/* THE FUNCTIONS BELOW ARE DEDICATED TO THE HSV STRUCT*/

struct HSV ** init_HSV(int rows, int cols){
	struct HSV ** hsv_arr;
	hsv_arr = new struct HSV * [rows];
	for(int i = 0; i < rows; i++){
		hsv_arr[i] = new struct HSV [cols];	
	}
	return hsv_arr;
}

void populate_HSV(struct RGB ** rgb_arr, struct HSV ** hsv_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			// hsv_arr[i][j].hue = 0;
            // hsv_arr[i][j].saturation = 0;
            // hsv_arr[i][j].value = 0;	
            RGB2HSV(rgb_arr[i][j], hsv_arr[i][j]);
		}	
	}
}

void print_HSV(struct HSV ** hsv_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			cout << hsv_arr[i][j].hue << hsv_arr[i][j].saturation << hsv_arr[i][j].value << " ";	
		}	
		cout << endl;
	}
}

void delete_HSV(struct HSV ** hsv_arr, int rows, int cols){
	for(int i = 0; i < rows; i++){
		delete [] hsv_arr[i];	
	}
	delete [] hsv_arr;
}

/* THE FUNCTIONS BELOW CONVERT THE RGB TO HSV*/

static int Min(int a, int b) {
	return a <= b ? a : b;
}

static int Max(int a, int b) {
	return a >= b ? a : b;
}

void RGB2HSV(struct RGB rgb, struct HSV hsv){
    double delta, min;
    


    cout << rgb.red<< endl;
    min = Min(Min(rgb.red, rgb.green), rgb.blue);
   hsv.value= Max(Max(rgb.red, rgb.green), rgb.blue);
    delta =hsv.value- min;
    
    if(hsv.value == 0.0){
       hsv.saturation = 0;
    }
    else{
       hsv.saturation = delta / hsv.value;
    }
    
    if(hsv.saturation == 0){
        hsv.hue= 0.0;
    }
    else{
        if(rgb.red == hsv.value){
            hsv.hue  = (rgb.green - rgb.blue) / delta;
        }
        else if(rgb.green == hsv.value){
            hsv.hue= 2 + (rgb.blue - rgb.red) / delta;
        }
        else if(rgb.blue == hsv.value){
            hsv.hue = 4 + (rgb.red - rgb.green) / delta;
        }
        hsv.hue *= 60;
        
        if(hsv.hue < 0.0){
            hsv.hue = hsv.hue + 360;
        }
    }
    
   hsv.value = hsv.value/ 255;
}
