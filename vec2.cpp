#include "vec2.h"
#include <cmath>
#define PI 3.14159265359


vec2::vec2() : x{ 0 }, y{ 0 } {};
vec2::~vec2() {};
vec2::vec2(float x, float y) : x{ x }, y{ y } {}
vec2::vec2(const vec2& other) : x{ other.x }, y{ other.y } {}

vec2& vec2::operator=(const vec2& other) {
	x = other.x;
	y = other.y;
	return *this;
}

vec2 vec2::operator+(const vec2& other) const {
	return vec2(x + other.x, y + other.y);
}
vec2 vec2::operator-(const vec2& other) const {
	return vec2(x - other.x, y - other.y);
}

vec2& vec2::operator+=(const vec2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

vec2& vec2::operator-=(const vec2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

vec2& vec2::operator*=(const float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

// Scalar operations
vec2 vec2::operator+(const float& c) const {
	return vec2(x + c, y + c);
}
vec2 vec2::operator-(const float& c) const {
	return vec2(x - c, y - c);
}
vec2 vec2::operator*(const float& c) const {
	return vec2(x * c, y * c);
}
vec2 vec2::operator/(const float& c) const {
	return vec2(x / c, y / c);
}
void vec2::set(float x, float y) {
	this->x = x;
	this->y = y;
}

void vec2::rotate(float deg) {
	float theta = deg / 180.0 * PI;
	float c = cos(theta);
	float s = sin(theta);
	float tx = x * c - y * s;
	float ty = x * s + y * c;
	x = tx;
	y = ty;
}

vec2& vec2::normalize() {
	if (length() == 0) return *this;
	*this *= (1.0 / length());
	return *this;
}

float vec2::dist(vec2 v) const {
	vec2 d(v.x - x, v.y - y);
	return d.length();
}
float vec2::length() const {
	return std::sqrt(x * x + y * y);
}
void vec2::truncate(float length) {
	float angle = atan2f(y, x);
	x = length * cos(angle);
	y = length * sin(angle);
}

vec2 vec2::ortho() const {
	return vec2(y, -x);
}

float vec2::dot(vec2 v1, vec2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
float vec2::cross(vec2 v1, vec2 v2) {
	return (v1.x * v2.y) - (v1.y * v2.x);
}

const float vec2::cross(vec2 v2) const
{
	return (x * v2.y) - (y * v2.x);
}