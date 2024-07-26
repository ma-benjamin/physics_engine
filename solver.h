#ifndef SOLVER_H
#define SOLVER_H

#include "vec2.h"

struct Solver
{

	const vec2 gravity = vec2(0.0f, 0.3f);

	void update(float dt);
	void updatePositions(float dt);
	void applyGravity();
};

#endif