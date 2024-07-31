#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Circle
{
public:
	GLfloat* vertices;
	GLuint* indices;
	int steps;
	float radius;
	

	Circle(float centerX, float centerY, float r, int s);
	Circle(float centerX, float centerY, float r, int s, float rv, float gv, float bv);

	~Circle();

	void updatePosition(float x, float y);
};

#endif