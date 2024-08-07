#include "verletObject.h"

verletObject::verletObject(vec2 pc, vec2 po, vec2 a, float r) {
	position_current = pc;
	position_old = po;
	acceleration = a;
	radius = r;
	ID = -1;
}
 
verletObject::~verletObject() {}

void verletObject::updatePosition(float dt) {
	const vec2 velocity = position_current - position_old;
	position_old = position_current;
	position_current = position_current + velocity + acceleration * dt * dt;

	if (position_current.y - radius < -0.95) {
		position_current.y = -0.95 + radius;
	}

	acceleration = vec2{ 0,0 };


}

void verletObject::accelerate(vec2 acceleration_new) {
	acceleration += acceleration_new;
}

