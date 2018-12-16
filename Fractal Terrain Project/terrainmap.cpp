#include "terrainmap.h"

using namespace std;

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
	temp->point1->x = pt1->x;
	temp->point1->y = pt1->y;
	temp->point1->z = pt1->z;

	//Assigning pt2 to triangle pt2
	temp->point2->x = pt2->x;
	temp->point2->y = pt2->y;
	temp->point2->z = pt2->z;

	//Assigning pt3 to triangle pt3
	temp->point3->x = pt3->x;
	temp->point3->y = pt3->y;
	temp->point3->z = pt3->z;

	return temp;
}

void add_to_vector(vector<triangle> v, triangle* tri) {
	v.push_back(tri);
}

void hsv_to_triangle(HSV** hsv, vector<triangle> v, int rows, int cols) {
	int h1, h2, h3, h4;
	point* p1, p2, p3, p4;
	triangle* t1, t2;
	for (int i = 0; i < rows, i++) {
		for (int j = 0; j < cols; j++) {
			//Create height values
			h1 = HSV[i][j];
			h2 = HSV[i][j + 1];
			h3 = HSV[i + 1][j];
			h4 = HSV[i + 1][j + 1];

			//Create point values
			p1 = create_point(i, j, h1);
			p2 = create_point(i, j + 1, h2);
			p3 = create_point(i + 1, j, h3);
			p4 = create_point(i + 1, j + 1, h4);

			//Create triangle values
			//If running into errors, try switcing p2->p3 and p3->p2 below
			t1 = create_triangle(p1, p2, p4);
			t2 = create_triangle(p1, p3, p4);

			//Add triangles to vector
			add_to_vector(v, t1);
			add_to_vector(v, t2);
		}
	}
}