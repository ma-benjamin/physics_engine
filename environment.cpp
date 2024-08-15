#include "environment.h"

Environment::Environment() {};

Environment::~Environment() {
	m_objects.clear();
};

void Environment::AddObject(verletObject* ob) {
	m_objects.push_back(ob);
	ob->ID = m_objects.size();
}

void Environment::AddObject(float xpos, float ypos, float radius, vec2 velocity) {
	verletObject* v = new verletObject(vec2(xpos, ypos), vec2(xpos - velocity.x, ypos - velocity.y), vec2(), radius);
	AddObject(v);
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
	const float response_coef = 0.75f;
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

void Environment::addObjectsToGrid() {
	grid.clear();
	int i = 0;
	for (const verletObject* obj : m_objects) {
		int translated_x = (obj->position_current.x + 1) * WIDTH / 2;
		int translated_y = (-obj->position_current.y + 1) * HEIGHT / 2;
		grid.addAtom(translated_x, translated_y, i);
		++i;
	}
};

void Environment::solveContact(int idx1, int idx2) {
	const float response_coef = 1.0f;
	const float eps = 0.0001f;
	verletObject* obj1 = m_objects.at(idx1);
	verletObject* obj2 = m_objects.at(idx2);
	const float dist = (obj1->position_current).dist(obj2->position_current);

	if (dist < 1.0f && dist > eps) {
		const float delta = response_coef * 0.5f * (1.0f - dist);
		const vec2 col_vec = (obj1->position_current - obj2->position_current) / dist * delta;
		obj1->position_current += col_vec;
		obj2->position_current -= col_vec;
	}

};

void Environment::checkAtomCellCollisions(int atom_idx, const CollisionCell& c) {
	for (int i = 0; i < c.objects_count; ++i) {
		solveContact(atom_idx, c.objects[i]);
	}
};

void Environment::processCell(const CollisionCell& c, int index) {
	for (int i = 0; i < c.objects_count; ++i) {
		const int atom_idx = c.objects[i];
		checkAtomCellCollisions(atom_idx, grid.data[index - 1]);
		checkAtomCellCollisions(atom_idx, grid.data[index]);
		checkAtomCellCollisions(atom_idx, grid.data[index + 1]);
		checkAtomCellCollisions(atom_idx, grid.data[index + grid.height - 1]);
		checkAtomCellCollisions(atom_idx, grid.data[index + grid.height]);
		checkAtomCellCollisions(atom_idx, grid.data[index + grid.height + 1]);
		checkAtomCellCollisions(atom_idx, grid.data[index - grid.height - 1]);
		checkAtomCellCollisions(atom_idx, grid.data[index - grid.height]);
		checkAtomCellCollisions(atom_idx, grid.data[index - grid.height + 1]);
	}
};

void Environment::solveCollision() {
	for (int i = 0; i < grid.data.size(); ++i) {
		processCell(grid.data[i], i);
	}
};