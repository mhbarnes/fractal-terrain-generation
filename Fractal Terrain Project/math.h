#ifndef MATH
#define MATH

#include <stdlib.h>
#include <time.h>
#include "color.h"

int RandInt(int min, int max);

double RandDouble(double min, double max);

RGB RandColorRGB();

HSV RandColorHSV();

#endif