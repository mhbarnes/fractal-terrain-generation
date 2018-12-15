#ifndef TERRAINMAP_H
#define TERRAINMAP_H

//Structs
struct point {
	int x;
	int y;
	int z;
};

struct triangle {
	int point1;
	int point2;
	int point3;
};

//Functions
int map_to_height(int*);
point* map_to_point(int, int, int)


#endif
