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
#include "utils.h"
#include <chrono>

void compile_circles(GLfloat* all_vertices, GLuint* all_indices, std::vector<verletObject*> obs);

//Environment world;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos;
		double ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << xpos/WIDTH << ',' << ypos/HEIGHT << std::endl;
		verletObject* a = new verletObject(vec2(xpos / WIDTH, ypos / HEIGHT), 
										   vec2(xpos / WIDTH, ypos / HEIGHT), 
										   vec2(0.0f, 0.0f), 
										   0.05f);
		//world.AddObject(a);
	}
}





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

	float radius = 0.05f;

	vec2 pc = vec2(0.0f, 0.0f);
	vec2 po;
	vec2 a;

	verletObject* v = new verletObject(pc, po, a, radius );
	verletObject* x = new verletObject(vec2(0.7f, 0.0f), vec2(0.5f, 0.0f), a, radius);
	verletObject* y = new verletObject(vec2(0.0f, 0.3f), vec2(0.0f, 0.3f), a, radius);
	verletObject* nx = new verletObject(vec2(-0.7f, 0.0f), vec2(-0.5f, 0.0f), a, radius);
	verletObject* ny = new verletObject(vec2(0.0f, -0.3f), vec2(0.0f, -0.3f), a, radius);

	Environment world;
	world.AddObject(v);
	world.AddObject(x);
	world.AddObject(y);
	world.AddObject(nx);
	world.AddObject(ny);

	verletObject* ax = new verletObject(vec2(0.3f, 0.0f), vec2(0.5f, 0.0f), a, radius);
	verletObject* ay = new verletObject(vec2(0.0f, 0.1f), vec2(0.0f, 0.1f), a, radius);
	verletObject* anx = new verletObject(vec2(-0.3f, 0.0f), vec2(-0.3f, 0.0f), a, radius);
	verletObject* any = new verletObject(vec2(0.0f, -0.6f), vec2(0.0f, -0.6f), a, radius);

	world.AddObject(ax);
	world.AddObject(ay);
	world.AddObject(anx);
	world.AddObject(any);
	
	
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "physics", NULL, NULL);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

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

	Circle border(0.0f, 0.0f, (float) 800.0f / HEIGHT, 100, 0.6f, 0.6f, 0.6f);
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
    glViewport(0, 0, WIDTH, HEIGHT);

	Shader shaderProgram("default.vert", "default.frag");

	std::chrono::seconds dura(20);

	float pressed = 0;
	//glfwSetMouseButtonCallback(window, mouse_button_callback);

	int num_objs = world.returnObjects().size();
	GLfloat* all_vertices = new GLfloat[num_objs * (STEPS + 1) * 6];
	GLuint* all_indices = new GLuint[num_objs * STEPS * 3];
	compile_circles(all_vertices, all_indices, world.returnObjects());

	float frames = 120;
	float time = 0;
	float substep = 4;
	float dt = 0.1 / frames;
	float stepdt = dt / substep;


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // navy
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		// border
		vaoB.Bind();
		glDrawElements(GL_TRIANGLES, 3 * border.steps, GL_UNSIGNED_INT, 0);
		vaoB.Unbind();

		int mouseState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (mouseState == GLFW_PRESS) {
			if (time - pressed > 3.5) {
				pressed = time;
				std::cout << "pressed at " << time << std::endl;
				double xpos;
				double ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				std::cout << xpos << ',' << ypos << std::endl;
				float scaled_x = (xpos - (WIDTH / 2)) / (WIDTH / 2);
				float scaled_y = -1 * (ypos - (HEIGHT / 2)) / (HEIGHT / 2);
				std::cout << scaled_x << ',' << scaled_y << std::endl;
				verletObject* ab = new verletObject(vec2(scaled_x, scaled_y), vec2(scaled_x, scaled_y), a, radius);
				world.AddObject(ab);

				GLfloat* temp_v = all_vertices;
				GLuint* temp_i = all_indices;

				num_objs = world.returnObjects().size();
				all_vertices = new GLfloat[num_objs * (STEPS + 1) * 6];
				all_indices = new GLuint[num_objs * STEPS * 3];

				delete[] temp_v;
				delete[] temp_i;
			}
		}

		compile_circles(all_vertices, all_indices, world.returnObjects());

		VAO tvao;
		tvao.Bind();
		VBO tvbo(all_vertices, sizeof(float) * (STEPS + 1) * 6 * num_objs);
		EBO tebo(all_indices, sizeof(float) * (STEPS) * 3 * num_objs);

		tvao.LinkAttrib(tvbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		tvao.LinkAttrib(tvbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glDrawElements(GL_TRIANGLES, num_objs * 3 * STEPS, GL_UNSIGNED_INT, 0);
		tvao.Unbind();
		tvbo.Unbind();
		tebo.Unbind();

		tvao.Delete();
		tvbo.Delete();
		tebo.Delete();



		for (int i = 0; i < substep; i++) {
			world.applyGravity();
			world.checkCollisions(stepdt);
			world.applyConstraint();
			world.Step(stepdt);
		}
		
		//world.applyGravity();
		//world.checkCollisions(dt);
		//world.applyConstraint();
		//world.Step(dt);
		//world.checkCollisions(dt);
		//world.applyConstraint();

		glfwSwapBuffers(window);

		glfwPollEvents();

		time += dt;
		
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
	int v_temp = 0;
	int i_temp = 0;
	for (verletObject* obj : obs) {
		Circle c(obj->position_current.x, obj->position_current.y, obj->radius, STEPS);
		for (int i = 0; i <= STEPS; i++) {
			all_vertices[i * 6 + v_temp] = c.vertices[i * 6];
			all_vertices[i * 6 + 1 + v_temp] = c.vertices[i * 6 + 1];
			all_vertices[i * 6 + 2 + v_temp] = c.vertices[i * 6 + 2];
			all_vertices[i * 6 + 3 + v_temp] = c.vertices[i * 6 + 3];
			all_vertices[i * 6 + 4 + v_temp] = c.vertices[i * 6 + 4];
			all_vertices[i * 6 + 5 + v_temp] = c.vertices[i * 6 + 5];
		}

		for (int i = 0; i < STEPS * 3; i++) {
			all_indices[i + i_temp] = c.indices[i] + v_temp/6;
		}

		v_temp += (STEPS + 1) * 6;
		i_temp += (STEPS) *3;

	}
}