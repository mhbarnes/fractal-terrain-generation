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
bitmap_image FeedbackFractal(bitmap_image main, bitmap_image& temp, double saturationDist, double valueDistance, double rotationDegrees, double zoomFactor)
{
	// 1. Each pixel RGB in the main bitmap is converted to HSL. The HSL values are used as an
	//    angle and a distance. The angle and distance then point to a new pixel location on the
	//    temp bitmap.The main bitmap pixel is the colored using the temp bitmap pixel color.
	for (unsigned int i = 0; i < main.width(); i++)
		for (unsigned int j = 0; j < main.height(); j++)
		{
			HSV hsv = BitmapToHSV(main.get_pixel(i, j));

			double angle = hsv.hue;
			double distance = hsv.saturation*saturationDist + hsv.value*valueDistance;
			
			int x = distance * cos(angle) + i;
			int y = distance * sin(angle) + j;

			int xNew = x % main.width() + (x % main.width() < 0 ? main.width() : 0);
			int yNew = y % main.height() + (y % main.height() < 0 ? main.height() : 0);

			main.set_pixel(i, j, temp.get_pixel(xNew, yNew));
		}
	
	// 2. Sharpen the main bitmap.
	main = Sharpen(main);

	// 3. Blur the main bitmap.
	main = Blur(main);

	// 4. Save the main bitmap.

	// 5. Blend the main bitmap with the temp bitmap.
	temp = BlendImages(main, temp);

	// 6. Rotate the temp bitmap.
	temp = RotateImage(temp, rotationDegrees);

	// 7. Histogram equalize the temp bitmap.
	temp = HistogramEqualize(temp);

	// 8. Zoom the temp bitmap
	temp = ZoomImage(temp, zoomFactor);

	return main;
}

bitmap_image BlendImages(bitmap_image a, bitmap_image b)
{
	bitmap_image bmp(a.width(), a.height());

	for (unsigned int i = 0; i < a.width(); i++)
		for (unsigned int j = 0; j < a.height(); j++)
			bmp.set_pixel(i, j, RGBToBitmap(MergeRGB(BitmapToRGB(a.get_pixel(i, j)), BitmapToRGB(b.get_pixel(i, j)))));
			//bmp.set_pixel(i, j, HSVToBitmap(MergeHSV(BitmapToHSV(a.get_pixel(i, j)), BitmapToHSV(b.get_pixel(i, j)))));

	return bmp;
}

bitmap_image RotateImage(bitmap_image bmp, double degrees)
{
	return bmp;
}

bitmap_image HistogramEqualize(bitmap_image bmp)
{
	bitmap_image output(bmp.width(), bmp.height());

	for (unsigned int i = 0; i < bmp.width(); i++)
		for (unsigned int j = 0; j < bmp.height(); j++)
		{
			double value = -50; // -100 <> 100
			RGB pixel = BitmapToRGB(bmp.get_pixel(i, j));

			float red = pixel.red / 255.0f;
			float green = pixel.green / 255.0f;
			float blue = pixel.blue / 255.0f;

			red = (((red - 0.5f) * value) + 0.5f) * 255.0f;
			green = (((green - 0.5f) * value) + 0.5f) * 255.0f;
			blue = (((blue - 0.5f) * value) + 0.5f) * 255.0f;

			output.set_pixel(i, j, RGBToBitmap(CreateRGB(red, green, blue)));
		}

	return output;
}

bitmap_image ZoomImage(bitmap_image bmp, double factor)
{
	return bmp;
}

bitmap_image StaticNoise(int xRes, int yRes)
{
	bitmap_image bmp(xRes, yRes);

	for (unsigned int x = 0; x < bmp.width(); x++)
		for (unsigned int y = 0; y < bmp.height(); y++)
			bmp.set_pixel(x, y, RGBToBitmap(RandColorRGB()));

	return bmp;
}

bitmap_image Blur(bitmap_image bmp)
{
	return bmp;
}

bitmap_image Sharpen(bitmap_image bmp)
{
	return bmp;
}