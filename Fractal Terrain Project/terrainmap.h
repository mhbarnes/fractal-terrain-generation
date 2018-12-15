#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include <iostream>
#include <cmath>
#include <vector>

//Structs
struct point {
	int x;
	int y;
	int z;
};

struct triangle {
	point1 point1;
	point2 point2;
	point3 point3;
};

//Functions
point* create_point(int, int, int);
triangle* create_triangle(point*, point*, point*)

#endif
