#include "verletObject.h"

verletObject::verletObject(vec2 pc, vec2 po, vec2 a, float r) {
	position_current = pc;
	position_old = po;
	acceleration = a;
	ID = NULL;
	circle = new Circle(position_current.x, position_current.y, r, 100);
}
 
verletObject::~verletObject() {
	delete circle;
}

void verletObject::updatePosition(float dt) {
	const vec2 velocity = position_current - position_old;
	position_old = position_current;
	position_current = position_current + velocity + acceleration * dt * dt;
	float displaceX = position_current.x - position_old.x;
	float displaceY = position_current.y - position_old.y;
	circle->updatePosition(displaceX, displaceY);
	acceleration = vec2{ 0,0 };
}

void verletObject::accelerate(vec2 acceleration_new) {
	acceleration += acceleration_new;
}