#include "fractal.h"

/*
Initialisation
1. Create 2 bitmaps for a main layer and a temp layer
2. Fill them both with random static

Main loop
1. Each pixel RGB in the main bitmap is converted to HSL.The HSL values are used as an angle and a distance.The angle and distance then points to a new pixel location on the temp bitmap.The main bitmap pixel is the colored using the temp bitmap pixel color.
2. Sharpen the main bitmap.
3. Blur the main bitmap.
4. Display the main bitmap.
5. Blend the main bitmap with the temp bitmap.
6. Rotate the temp bitmap.
7. Histogram equalise the temp bitmap.This is similar to how Photoshop does auto - contrast.
8. Zoom the temp bitmap.
*/
bitmap_image FeedbackFractal(bitmap_image main, bitmap_image& temp, double saturationDist, double valueDistance)
{
	// 1. Each pixel RGB in the main bitmap is converted to HSL. The HSL values are
	//    used as an angle and a distance. The angle and distance then points to a
	//    new pixel location on the temp bitmap.The main bitmap pixel is the colored
	//	  using the temp bitmap pixel color.

	for (unsigned int x = 0; x < main.width(); x++)
		for (unsigned int y = 0; y < main.height(); y++)
		{
			HSV hsv = RGB2HSV((double) main.get_pixel(x, y).red, (double) main.get_pixel(x, y).red, (double) main.get_pixel(x, y).red);


		}

	return main;
}

bitmap_image StaticNoise(int xRes, int yRes)
{
	bitmap_image bmp(xRes, yRes);

	for (unsigned int x = 0; x < bmp.width(); x++)
		for (unsigned int y = 0; y < bmp.height(); y++)
		{
			bmp.set_pixel(x, y, RGBToBitmap(RandColorRGB()));
		}

	return bmp;
}

bitmap_image Blur(bitmap_image bmp)
{
	bitmap_image garbage(0, 0);

	return garbage;
}

bitmap_image Sharpen(bitmap_image bmp)
{
	bitmap_image trash(0, 0);

	return trash;
}