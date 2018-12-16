#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include "color.h"
#include "bitmap_image.hpp"

bitmap_image sharpen(&bitmap_image);
bitmap_image box_blur(&bitmap_image);
bitmap_image gauss_blur(&bitmap_image);

#endif