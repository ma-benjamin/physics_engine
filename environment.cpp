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
