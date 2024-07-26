#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include <math.h>


GLuint SCREEN_HEIGHT = 800;
GLuint SCREEN_WIDTH = 1000;

//int main()
//{
//	// Initialize GLFW
//	glfwInit();
//
//	// Tell GLFW what version of OpenGL we are using
//	// In this case we are using OpenGL 3.3
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	// Tell GLFW we are using the CORE prrofile
//	// So that means we only have the modern functions
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLfloat vertices[] =
//	{ //               COORDINATES                  /     COLORS           //
//		-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
//		 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
//		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
//		-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
//		 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
//		 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
//	};
//
//	GLuint indices[] =
//	{
//		0, 3, 5,
//		3, 2, 4,
//		5, 4, 1
//	};
//
//	// Creating a window named physics
//	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "physics", NULL, NULL);
//
//	// error check is window fail to create
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	// introduce window into tthe current context
//	glfwMakeContextCurrent(window);
//
//	//load glad ato configures opengl
//	gladLoadGL();
//
//	//specify the viewport of open in the window
//	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
//
//	Shader shaderProgram("default.vert", "default.frag");
//
//	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
//
//	// Generate VAO and VBO with only one object in it
//	VAO vao;
//	vao.Bind();
//	VBO vbo(vertices, sizeof(vertices));
//	EBO ebo(indices, sizeof(indices));
//
//	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
//	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//
//	vao.Unbind();
//	vbo.Unbind();
//	ebo.Unbind();
//
//	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // navy
//		glClear(GL_COLOR_BUFFER_BIT);
//		//shaderProgram.Activate();
//		//glUniform1f(uniID, 0.5f);
//		//vao.Bind();
//		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
//		
//		
//
//		glfwSwapBuffers(window);
//
//		glfwPollEvents();
//	}
//
//	vao.Delete();
//	vbo.Delete();
//	ebo.Delete();
//	shaderProgram.Delete();
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//	return 0;
//}