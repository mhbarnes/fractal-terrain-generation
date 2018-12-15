#include "terrainmap.h"

point* create_point(int x, int y, int z) {
	point* temp = new point;
	temp->x = x;
	temp->y = y;
	temp->z = z;
	return temp;
}

triangle* create_triangle(point* pt1, point* pt2, point* pt3) {
	triangle* temp = new triangle;

	//Assigning pt1 to triangle pt1
	temp->point1.x = pt1->x;
	temp->point1.y = pt1->y;
	temp->point1.z = pt1->z;

	//Assigning pt2 to triangle pt2
	temp->point2.x = pt2->x;
	temp->point2.y = pt2->y;
	temp->point2.z = pt2->z;

	//Assigning pt3 to triangle pt3
	temp->point3.x = pt3->x;
	temp->point3.y = pt3->y;
	temp->point3.z = pt3->z;

	return temp;
}

void add_to_vector(vector<triangle>& v, triangle tri) {
	v.push_back(tri);
}


