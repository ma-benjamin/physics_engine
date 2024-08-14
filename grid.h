#pragma once

#include <vector>
#include <array>
#include "vec2.h"

template<typename T>
struct Grid {
	struct HitPoint {
		T* cell;
		float dist;

		HitPoint() {
			cell(nullptr);
			dist = 0.0f;
		};
		~HitPoint() {
			delete[] cell;
		};
	};

	int width, height;
	std::vector<T> data;

	Grid();
	Grid(int width, int height);
	~Grid();

	int mod(int dividend, int divisor) const;

	bool checkCoords(const vec2& v) const;
	bool checkCoords(int x, int y) const;

	const T& get(int x, int y) const;

	T& get(const vec2& v);

	const T& get(const vec2& v) const;

	const T& getWrap(vec2 v) const;
	const T& getWrap(int x, int y) const;

	T& get(int x, int y);

	void set(const vec2& v, const T& obj);
	void set(int x, int y, const T& obj);
};

