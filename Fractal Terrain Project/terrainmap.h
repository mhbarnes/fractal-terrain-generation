#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

//Structs
struct point
{
	int x;
	int y;
	int z;
};

struct triangle
{
	point point1;
	point point2;
	point point3;
};

//Functions
point* create_point(int, int, int);
triangle* create_triangle(point, point, point);
void add_to_vector(vector<triangle>&, triangle);

#endif
