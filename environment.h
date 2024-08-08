#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include "vec2.h"
#include "verletObject.h"
#include "shaderClass.h"

struct Environment {
private:
	std::vector<verletObject*> m_objects;
	vec2 m_gravity = vec2(0, -0.98f);
	vec2 m_center = vec2();
	int m_time = 0;

public:
	Environment();
	~Environment();
	void AddObject(verletObject* ob);
	void RemoveObject(verletObject* ob);
	std::vector<verletObject*> returnObjects();

	void Step(float dt);
	void applyGravity();
	void applyConstraint();
	void checkCollisions(float dt);
};

#endif
