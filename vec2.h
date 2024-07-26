#ifndef vec22_H
#define vec22_H

struct vec2 {
public:
	float x, y;

	vec2();
	~vec2();
	vec2(float x, float y);
	vec2(const vec2& other);

	vec2& operator=(const vec2& other);

	vec2 operator+(const vec2& other) const;
	vec2 operator-(const vec2& other) const;

	vec2& operator+=(const vec2& other);

	vec2& operator-=(const vec2& other);

	vec2& operator*=(const float scalar);

	// Scalar operations
	vec2 operator+(const float& c) const;
	vec2 operator-(const float& c) const;
	vec2 operator*(const float& c) const;
	vec2 operator/(const float& c) const;
	void set(float x, float y);

	void rotate(float deg);

	vec2& normalize();

	float dist(vec2 v) const;
	float length() const;
	void truncate(float length);

	vec2 ortho() const;

	static float dot(vec2 v1, vec2 v2);
	static float cross(vec2 v1, vec2 v2);

	const float cross(vec2 v2) const;

	const float dot(vec2 v2) const;

	const vec2 perpCCW() const;

	const vec2 perpCW() const;
};

#endif

