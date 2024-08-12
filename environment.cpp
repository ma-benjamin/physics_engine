#include "environment.h"

Environment::Environment() {
	//shaderProgram = new Shader("default.vert", "default.frag");
};

Environment::~Environment() {
	m_objects.clear();
};

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
		if (dist >= (1.0f - obj->radius)) {
			const vec2 n = (m_center - obj->position_current) / dist;
			obj->position_current = m_center - n * (1.0f - obj->radius);
		}
	}
}

std::vector<verletObject*> Environment::returnObjects() {
	return m_objects;
}

void Environment::checkCollisions(float dt) {
	const float response_coef = 1.25f;
	const int num_objects = m_objects.size();
	for (int i = 0; i < num_objects; ++i) {
		verletObject* ob1 = m_objects[i];

		for (int k = i + 1; k < num_objects; ++k) {
			verletObject* ob2 = m_objects[k];
			const float dist = ob1->position_current.dist(ob2->position_current);
			float min_dist = ob1->radius + ob2->radius;
			if (dist < min_dist) {
				const vec2 norm = (ob1->position_current - ob2->position_current).normalize();
				float mr1 = ob1->radius / (ob1->radius + ob2->radius);
				float mr2 = ob2->radius / (ob1->radius + ob2->radius);
				const float delta = 0.5f * response_coef * (dist - min_dist);

				
				//std::cout << dist << std::endl;
				//std::cout << min_dist << std::endl;
				//std::cout << norm.x << ',' << norm.y << std::endl;
				//std::cout << mr1 << ',' << mr2 << std::endl;
				//std::cout << delta << std::endl;
				//std::cout << "=============================" << std::endl;


				//ob1->position_old = ob1->position_current;
				//ob2->position_old = ob2->position_current;
				ob1->position_current -= norm * (mr2 * delta);
				ob2->position_current += norm * (mr1 * delta);
			}
		}
	}
}