#include "environment.h"

Environment::Environment() {
	//shaderProgram = new Shader("default.vert", "default.frag");
};

Environment::~Environment() {};

void Environment::AddObject(verletObject* ob) {
	m_objects.push_back(ob);
	ob->ID = m_objects.size();
	//VAO* vao = new VAO();
	//vao->Bind();
	//VBO* vbo = new VBO(ob->circle->vertices, sizeof(ob->circle->vertices) * (ob->circle->steps + 1) * 3);
	//EBO* ebo = new EBO(ob->circle->indices, sizeof(ob->circle->indices) * (ob->circle->steps + 1));

	//vaos.push_back(vao);
	//vbos.push_back(vbo);
	//ebos.push_back(ebo);

	//vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	//vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//vao->Unbind();
	//vbo->Unbind();
	//ebo->Unbind();
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

void Environment::draw() {
	//shaderProgram->Activate();
	//GLuint uniID = glGetUniformLocation(shaderProgram->ID, "scale");
	//glUniform1f(uniID, 0.5f);
	//for (int i = 0; i < vaos.size(); i++) {
	//	vaos.at(i)->Bind();
	//	std::cout << "problem" << std::endl;
	//	glDrawElements(GL_TRIANGLES, 3 * m_objects.at(i)->circle->steps, GL_UNSIGNED_INT, 0);
	//	vaos.at(i)->Unbind();
	//}
}