#include "environment.h"

Environment::Environment() {
	//shaderProgram = new Shader("default.vert", "default.frag");
};

Environment::~Environment() {};

void Environment::AddObject(verletObject* ob) {
	m_objects.push_back(ob);
	ob->ID = m_objects.size();
}

void Environment::RemoveObject(verletObject* ob) {
	if (!ob) return;
	if (ob->ID == NULL) return;
	if (m_objects.at(ob->ID) == ob) {
		m_objects.erase(m_objects.begin() + ob->ID - 1);
	}
}

void Environment::Step(float dt) {
	for (verletObject* obj : m_objects) {
		obj->updatePosition(dt);
	}
}

void Environment::applyGravity() {
	for (verletObject* obj : m_objects) {
		obj->accelerate(m_gravity);
	}
}

void Environment::applyConstraint() {
	for (verletObject* obj : m_objects) {
		const float dist = m_center.dist(obj->position_current);
		if (dist > (1.0f - obj->circle->radius)) {
			const vec2 n = (m_center - obj->position_current) / dist;
			obj->position_current = m_center - n * (1.0f - obj->circle->radius);
		}
	}
}