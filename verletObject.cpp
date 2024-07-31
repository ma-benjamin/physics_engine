#include "verletObject.h"
#include <iostream>

verletObject::verletObject(vec2 pc, vec2 po, vec2 a, float r) {
	position_current = pc;
	position_old = po;
	acceleration = a;
	circle = new Circle(position_current.x, position_current.y, r, 100);
	ID = NULL;
}
 
verletObject::~verletObject() {
	delete circle;
}

void verletObject::updatePosition(float dt) {
	const vec2 velocity = position_current - position_old;
	position_old = position_current;
	position_current = position_current + velocity + acceleration * dt * dt;

	if (position_current.y - circle->radius < -0.95) {
		position_current.y = -0.95 + circle->radius;
	}

	circle->updatePosition(position_current.x, position_current.y);
	acceleration = vec2{ 0,0 };


}

void verletObject::accelerate(vec2 acceleration_new) {
	acceleration += acceleration_new;
}