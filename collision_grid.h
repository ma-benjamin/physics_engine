#ifndef COLLISION_GRID_H
#define COLLISION_GRID_H

#include "vec2.h"
#include "grid.h"

struct CollisionCell {
	static const int cell_capacity = 4;
	static const int max_cell_idx = cell_capacity - 1;

	int objects_count = 0;
	int objects[cell_capacity] = {};

	CollisionCell();

	void addAtom(int id);
	void clear();
	void remove(int id);
};

struct CollisionGrid : public Grid<CollisionCell> {
	
	CollisionGrid();
	CollisionGrid(int width, int height);

	bool addAtom(int x, int y, int atom);
	void clear();
};

#endif
