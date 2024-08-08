#include "verletObject.h"
#include <iostream>

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


	//std::cout << dt << std::endl;
	//std::cout << acceleration.y << std::endl;
	//std::cout << velocity.y << std::endl;
	//std::cout << position_current.x << ',' << position_current.y << std::endl;
	//std::cout << (velocity + acceleration * dt * dt).y  << std::endl;
	//std::cout << "=============================" << std::endl;

	acceleration = vec2{ 0,0 };


}

void verletObject::accelerate(vec2 acceleration_new) {
	acceleration += acceleration_new;
}

