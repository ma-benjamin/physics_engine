#include "circle.h"
#include <cmath>

#include "shaderClass.h"

Circle::Circle(float centerX, float centerY, float r, const int s) {
	steps = s;
	radius = r;
	vertices = new GLfloat[(steps + 1) * 6];
	indices = new GLuint[steps * 3];
	vertices[0] = centerX;
	vertices[1] = centerY;
	vertices[2] = 0.0f;
	vertices[3] = 1.0f;
	vertices[4] = 1.0f;
	vertices[5] = 1.0f;

	const float twoPI = 2 * 3.14159265358979f;
	for (int i = 1; i <= steps; i++) {
		float angle = twoPI * (i - 1) / steps;
		float x = cos(angle) * radius;
		float y = sin(angle) * radius;

		vertices[i * 6] = centerX + x;
		vertices[i * 6 + 1] = centerY + y;
		vertices[i * 6 + 2] = 0.0f;
		vertices[i * 6 + 3] = 1.0f;
		vertices[i * 6 + 4] = 1.0f;
		vertices[i * 6 + 5] = 1.0f;

		indices[(i - 1) * 3] = 0;
		indices[(i - 1) * 3 + 1] = i;
		if (i == steps) {
			indices[(i - 1) * 3 + 2] = 1;
		}
		else {
			indices[(i - 1) * 3 + 2] = i + 1;
		}
	}
}

Circle::Circle(float centerX, float centerY, float r, int s, float rv, float gv, float bv) {
	steps = s;
	radius = r;
	vertices = new GLfloat[(steps + 1) * 6];
	indices = new GLuint[steps * 3];
	vertices[0] = centerX;
	vertices[1] = centerY;
	vertices[2] = 0.0f;
	vertices[3] = rv;
	vertices[4] = gv;
	vertices[5] = bv;

	const float twoPI = 2 * 3.14159265358979f;
	for (int i = 1; i <= steps; i++) {
		float angle = twoPI * (i - 1) / steps;
		float x = cos(angle) * radius;
		float y = sin(angle) * radius;

		vertices[i * 6] = centerX + x;
		vertices[i * 6 + 1] = centerY + y;
		vertices[i * 6 + 2] = 0.0f;
		vertices[i * 6 + 3] = rv;
		vertices[i * 6 + 4] = gv;
		vertices[i * 6 + 5] = bv;

		indices[(i - 1) * 3] = 0;
		indices[(i - 1) * 3 + 1] = i;
		if (i == steps) {
			indices[(i - 1) * 3 + 2] = 1;
		}
		else {
			indices[(i - 1) * 3 + 2] = i + 1;
		}
	}
}

Circle::~Circle() {
	delete vertices;
	delete indices;
};

void Circle::updatePosition(float x, float y) {
	float displaceX = x - vertices[0];
	float displaceY = y - vertices[1];
	for (int i = 0; i <= steps; i++) {
		vertices[i * 6] += displaceX;
		vertices[i * 6 + 1] += displaceY;
	}
};
