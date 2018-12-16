#ifndef FRACTAL
#define FRACTAL

#include "bitmap_image.hpp"
#include "color.h"
#include "math.h"

bitmap_image FeedbackFractal(bitmap_image main, bitmap_image& temp, double saturationDist, double valueDistance, double rotationDegrees, double zoomFactor);

bitmap_image BlendImages(bitmap_image a, bitmap_image b);

bitmap_image RotateImage(bitmap_image bmp, double degrees);

bitmap_image HistogramEqualize(bitmap_image bmp);

bitmap_image ZoomImage(bitmap_image bmp, double factor);

bitmap_image StaticNoise(int xRes, int yRes);

bitmap_image Blur(bitmap_image bmp);

bitmap_image Sharpen(bitmap_image bmp);


#endif