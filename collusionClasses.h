#ifndef COLLUSION_CLASSES_H
#define COLLUSION_CLASSES_H

#include "vec2.h"

struct CollisionPoints {
	vec2 A;
	vec2 B;
	vec2 Normal;
	float depth;
	bool collide;
};

struct Transform {
	vec2 position;
	vec2 scale;
};

struct Collider {
	virtual CollisionPoints TestCollisions(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform) const = 0;
};

struct SphereCollider : Collider {};

struct PlaneCollider : Collider {};

#endif
