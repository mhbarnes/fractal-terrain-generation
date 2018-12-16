#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include "color.h"
#include "bitmap_image.hpp"

bitmap_image sharpen(&bitmap_image);
bitmap_image box_blur(&bitmap_image);
bitmap_image gauss_blur(&bitmap_image);
//gauss_blur() helper functions
void top_left(RGB [][3], &bitmap_image);
void top_right(RGB[][3], &bitmap_image);
void bot_left(RGB[][3], &bitmap_image);
void bot_right(RGB[][3], &bitmap_image);
void top_edge(RGB[][3], &bitmap_image);
void left_edge(RGB[][3], &bitmap_image);
void right_edge(RGB[][3], &bitmap_image);
void bot_edge(RGB[][3], &bitmap_image);

#endif