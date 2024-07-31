#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include <cmath>
#include "circle.h"
#include "environment.h"
#include "verletObject.h"
#include <vector>

void compile_circles(GLfloat* all_vertices, GLuint* all_indices, std::vector<verletObject*> obs);

int main() {
    // Initialize GLFW
	glfwInit();
	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE prrofile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	float radius = 0.05;

	Circle* circ;
	vec2 pc = vec2(0.0f, 0.0f);
	vec2 po;
	vec2 a;

	verletObject* v = new verletObject(pc, po, a, radius );
	verletObject* x = new verletObject(vec2(0.3f, 0.0f), vec2(0.3f, 0.0f), a, radius);
	verletObject* y = new verletObject(vec2(0.0f, 0.3f), vec2(0.0f, 0.3f), a, radius);
	verletObject* nx = new verletObject(vec2(-0.3f, 0.0f), vec2(-0.3f, 0.0f), a, radius);
	verletObject* ny = new verletObject(vec2(0.0f, -0.3f), vec2(0.0f, -0.3f), a, radius);

	Environment world;
	world.AddObject(v);
	world.AddObject(x);
	world.AddObject(y);
	world.AddObject(nx);
	world.AddObject(ny);

	circ = x->circle;
	
	std::vector<verletObject*> objects;
	objects.push_back(v);
	objects.push_back(x);
	objects.push_back(y);
	objects.push_back(nx);
	objects.push_back(ny);

	int num_objs = objects.size();
	GLfloat* all_vertices = new GLfloat[num_objs * (circ->steps + 1) * 6];
	GLuint* all_indices = new GLuint[num_objs * circ->steps * 3];

	compile_circles(all_vertices, all_indices, world.returnObjects());

	// printing all vertices
	//for (int i = 1; i < (circ->steps * 6 + 6) * 2; i++) {
	//	if (i % 6 == 0 && i > 0) {
	//		std::cout << std::endl;
	//	}
	//	std::cout << all_vertices[i] << ',';
	//	/*std::cout << circ->vertices[i] << ',' << std::endl;*/
	//}
	//std::cout << std::endl;
	//for (int i = 0; i < circ->steps * 6; i++) {
	//	if (i % 3 == 0 && i > 0) {
	//		std::cout << std::endl;
	//	}
	//	std::cout << all_indices[i] << ',';
	//}
	//std::cout << std::endl;

    GLFWwindow* window = glfwCreateWindow(800, 800, "physics", NULL, NULL);

    // error check is window fail to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // introduce window into the current context
    glfwMakeContextCurrent(window);
    //load glad ato configures opengl
    gladLoadGL();

	Circle border(0.0f, 0.0f, 0.8f, 100, 0.6f, 0.6f, 0.6f);
	VAO vaoB;
	vaoB.Bind();
	VBO vboB(border.vertices, sizeof(border.vertices) * (border.steps + 1) * 6);
	EBO eboB(border.indices, sizeof(border.indices) * border.steps * 3);

	vaoB.LinkAttrib(vboB, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vaoB.LinkAttrib(vboB, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	vaoB.Unbind();
	vboB.Unbind();
	eboB.Unbind();

    //specify the viewport of open in the window
    glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	float dt = 0;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // navy
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		// border
		vaoB.Bind();
		glDrawElements(GL_TRIANGLES, 3 * border.steps, GL_UNSIGNED_INT, 0);
		vaoB.Unbind();


		VAO tvao;
		tvao.Bind();
		VBO tvbo(all_vertices, sizeof(all_vertices) * (circ->steps + 1) * 6 * num_objs);
		EBO tebo(all_indices, sizeof(all_indices) * (circ->steps) * 3 * num_objs);

		tvao.LinkAttrib(tvbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		tvao.LinkAttrib(tvbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glDrawElements(GL_TRIANGLES, num_objs * 3 * circ->steps, GL_UNSIGNED_INT, 0);
		tvao.Unbind();
		tvbo.Unbind();
		tebo.Unbind();

		tvao.Delete();
		tvbo.Delete();
		tebo.Delete();

		for (int i = 0; i < 3; i++) {
			world.applyGravity();
			world.applyConstraint();
			world.Step(dt);
			world.applyConstraint();
		}
		compile_circles(all_vertices, all_indices, world.returnObjects());

		glfwSwapBuffers(window);

		glfwPollEvents();

		dt+= 0.00001;
	}

	shaderProgram.Delete();

	vaoB.Delete();
	vboB.Delete();
	eboB.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void compile_circles(GLfloat* all_vertices, GLuint* all_indices, std::vector<verletObject*> obs) {
	int num_objs = obs.size();
	int v_temp = 0;
	int i_temp = 0;
	for (verletObject* obj : obs) {
		Circle* c = obj->circle;
		for (int i = 0; i <= c->steps; i++) {
			all_vertices[i * 6 + v_temp] = c->vertices[i * 6];
			all_vertices[i * 6 + 1 + v_temp] = c->vertices[i * 6 + 1];
			all_vertices[i * 6 + 2 + v_temp] = c->vertices[i * 6 + 2];
			all_vertices[i * 6 + 3 + v_temp] = c->vertices[i * 6 + 3];
			all_vertices[i * 6 + 4 + v_temp] = c->vertices[i * 6 + 4];
			all_vertices[i * 6 + 5 + v_temp] = c->vertices[i * 6 + 5];
		}

		for (int i = 0; i < c->steps * 3; i++) {
			all_indices[i + i_temp] = c->indices[i] + v_temp/6;
		}

		v_temp += (c->steps + 1) * 6;
		i_temp += (c->steps) *3;

	}
}