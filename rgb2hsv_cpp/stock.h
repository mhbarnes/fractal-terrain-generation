#ifndef COLOR_H
#define COLOR_H
#include <iostream>

using namespace std;

void run_RGB(int rows, int cols);
struct RGB ** init_RGB(int rows, int cols);
void populate_RGB(struct RGB ** rgb_arr, int rows, int cols);
void print_RGB(struct RGB ** rgb_arr, int rows, int cols);
void delete_RGB(struct RGB ** rgb_arr, int rows, int cols);

void run_HSV(int rows, int cols);
struct HSV ** init_HSV(int rows, int cols);
void populate_HSV(struct RGB ** rgb_arr, struct HSV ** hsv_arr, int rows, int cols);
void print_HSV(struct HSV ** hsv_arr, int rows, int cols);
void delete_HSV(struct HSV ** hsv_arr, int rows, int cols);

static int Min(int a, int b);
static int Max(int a, int b);
void RGB2HSV(struct RGB ** rgb_arr, struct HSV ** hsv_arr);


#endif