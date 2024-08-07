#ifndef VERLET_OBJECT_H
#define VERLET_OBJECT_H

#include "vec2.h"

struct verletObject {
	vec2 position_current;
	vec2 position_old;
	vec2 acceleration;
	float radius;
	int ID;

	verletObject(vec2 pc, vec2 po, vec2 a, float r);

	~verletObject();

	void updatePosition(float dt);

	void accelerate(vec2 acceleration_new);
};

#endif

