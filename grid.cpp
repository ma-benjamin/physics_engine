#include "grid.h"

template<typename T>
Grid<T>::Grid() {
	width = 0;
	height = 0;
};

template<typename T>
Grid<T>::Grid(int w, int h) {
	width = w;
	height = h;
};

template<typename T>
Grid<T>::~Grid() {};

template<typename T>
int Grid<T>::mod(int dividend, int divisor) const {
	return (dividend % divisor);
};

template<typename T>
bool Grid<T>::checkCoords(const vec2& v) const {
	return checkCoords(static_cast<int>(v.x), static_cast<int>(v.y))
};

template<typename T>
bool Grid<T>::checkCoords(int x, int y) const {
	return static_cast<int>(x) > 0 && static_cast<int>(x) < (width - 1) &&
		static_cast<int>(y) > 0 && static_cast<int>(y) < (height - 1);
}

template<typename T>
const T& Grid<T>::get(int x, int y) const {
	return data[y * width + x];
};

template<typename T>
T& Grid<T>::get(const vec2& v) {
	return get(static_cast<int>(v.x), static_cast<int>(v.y));
};

template<typename T>
const T& Grid<T>::get(const vec2& v) const {
	return get(static_cast<int>(v.x), static_cast<int>(v.y));
};

template<typename T>
const T& Grid<T>::getWrap(vec2 v) const {
	return getWrap(v.x, v.y);
};

template<typename T>
const T& Grid<T>::getWrap(int x, int y) const {
	return get(mod(x, width), mod(y, height));
};

template<typename T>
T& Grid<T>::get(int x, int y) {
	return data[y * width + x];
};

template<typename T>
void Grid<T>::set(const vec2& v, const T& obj) {
	set(v.x, v.y, obj);
};

template<typename T>
void Grid<T>::set(int x, int y, const T& obj) {
	data[y * width + x] = obj;
};