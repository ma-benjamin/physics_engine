#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include "vec2.h"
#include "verletObject.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

struct Environment {
private:
	std::vector<verletObject*> m_objects;
	vec2 m_gravity = vec2(0, -9.81f);

public:
	Environment();
	~Environment();
	void AddObject(verletObject* ob);
	void RemoveObject(verletObject* ob);

	void Step(float dt);
	void draw();
};

#endif
