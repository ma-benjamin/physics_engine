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
	verletObject* x = new verletObject(vec2(0.3f, 0.0f), po, a, radius);
	verletObject* y = new verletObject(vec2(0.0f, 0.3f), po, a, radius);
	verletObject* nx = new verletObject(vec2(-0.3f, 0.0f), po, a, radius);
	verletObject* ny = new verletObject(vec2(0.0f, -0.3f), po, a, radius);

	Environment world;
	world.AddObject(v);

	circ = v->circle;
	
	std::vector<verletObject*> objects;
	objects.push_back(v);
	objects.push_back(x);
	objects.push_back(y);
	objects.push_back(nx);
	objects.push_back(ny);

	int num_objs = objects.size();
	GLfloat* all_vertices = new GLfloat[num_objs * (circ->steps + 1) * 6];
	GLuint* all_indices = new GLuint[num_objs * circ->steps * 3];

	compile_circles(all_vertices, all_indices, objects);

	// printing all vertices
	for (int i = 1; i < (circ->steps * 6 + 6) * 2; i++) {
		if (i % 6 == 0 && i > 0) {
			std::cout << std::endl;
		}
		std::cout << all_vertices[i] << ',';
		/*std::cout << circ->vertices[i] << ',' << std::endl;*/
	}
	std::cout << std::endl;
	for (int i = 0; i < circ->steps * 6; i++) {
		if (i % 3 == 0 && i > 0) {
			std::cout << std::endl;
		}
		std::cout << all_indices[i] << ',';
	}
	std::cout << std::endl;

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

    //specify the viewport of open in the window
    glViewport(0, 0, 800, 800);



	Shader shaderProgram("default.vert", "default.frag");

	//VAO vao;
	//vao.Bind();
	//VBO vbo(circ->vertices, sizeof(circ->vertices) * (circ->steps + 1) * 6);
	//EBO ebo(circ->indices, sizeof(circ->indices) * (circ->steps) * 3);

	//vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	//vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//vao.Unbind();
	//vbo.Unbind();
	//ebo.Unbind();

	//VAO vao1;
	//vao1.Bind();
	//VBO vbo1(circ1->vertices, sizeof(circ1->vertices) * (circ1->steps + 1) * 6);
	//EBO ebo1(circ1->indices, sizeof(circ1->indices) * (circ1->steps) * 3);

	//vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	//vao1.LinkAttrib(vbo1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	//vao1.Unbind();
	//vbo1.Unbind();
	//ebo1.Unbind();

	VAO tvao;
	tvao.Bind();
	VBO tvbo(all_vertices, sizeof(all_vertices) * (circ->steps + 1) * 6 * num_objs);
	EBO tebo(all_indices, sizeof(all_indices) * (circ->steps) * 3 * num_objs);

	tvao.LinkAttrib(tvbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	tvao.LinkAttrib(tvbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	tvao.Unbind();
	tvbo.Unbind();
	tebo.Unbind();
	

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	

    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // navy
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glUniform1f(uniID, 0.01f);
		tvao.Bind();
		glDrawElements(GL_TRIANGLES, num_objs * 3 * circ->steps, GL_UNSIGNED_INT, 0);
		tvao.Unbind();
		//vao1.Bind();
		//glDrawElements(GL_TRIANGLES, 3 * circ->steps, GL_UNSIGNED_INT, 0);
		//vao1.Unbind();
		/*v->updatePosition(1);*/

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	//vao.Delete();
	//vbo.Delete();
	//ebo.Delete();

	//vao1.Delete();
	//vbo1.Delete();
	//ebo1.Delete();

	tvao.Delete();
	tvbo.Delete();
	tebo.Delete();

	shaderProgram.Delete();

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