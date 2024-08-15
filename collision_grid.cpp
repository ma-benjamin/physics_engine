#include "collision_grid.h"

CollisionCell::CollisionCell() {};

void CollisionCell::addAtom(int id) {
	objects[objects_count] = id;
	objects_count += objects_count < max_cell_idx;
}

void CollisionCell::clear() {
	objects_count = 0;
}

void CollisionCell::remove(int id) {
	for (int i = 0; i < objects_count; ++i) {
		if (objects[i] == id) {
			objects[i] = objects[objects_count - 1];
			--objects_count;
			return;
		}
	}
}

CollisionGrid::CollisionGrid() : Grid<CollisionCell>() {}

CollisionGrid::CollisionGrid(int width, int height) : Grid<CollisionCell>(width, height) {};

bool CollisionGrid::addAtom(int x, int y, int atom) {
	const int id = x * height + y;
	data[id].addAtom(atom);
	return true;
}

void CollisionGrid::clear() {
	for (auto& c : data) {
		c.objects_count = 0;
	}
}