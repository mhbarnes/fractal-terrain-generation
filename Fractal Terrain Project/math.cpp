#include "math.h"

int RandInt(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

double RandDouble(double min, double max)
{
	return ((double) rand() / RAND_MAX) * (max - min) + min;
}

RGB RandColorRGB()
{
	return CreateRGB(RandInt(0, 255), RandInt(0, 255), RandInt(0, 255));
}

HSV RandColorHSV()
{
	return CreateHSV(RandDouble(0, 360), RandDouble(0, 1), RandDouble(0, 1));
}