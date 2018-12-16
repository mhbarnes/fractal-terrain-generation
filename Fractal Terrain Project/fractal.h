#ifndef FRACTAL
#define FRACTAL

#include "bitmap_image.hpp"
#include "color.h"
#include "math.h"

bitmap_image FeedbackFractal(bitmap_image main, bitmap_image& temp, double saturationDist, double valueDistance);

bitmap_image StaticNoise(int xRes, int yRes);

bitmap_image Blur(bitmap_image bmp);

bitmap_image Sharpen(bitmap_image bmp);


#endif