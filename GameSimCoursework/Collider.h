#pragma once
#include "PhysVector3.h"
#include "../nclgl/Matrix4.h"

class SphereCollider;

class Collider
{
public:
	Collider(Matrix4 transform = Matrix4()) : transform(transform) { }

	virtual bool Collides(PhysVector3& collisionPoint, const Collider& other) const = 0;
	virtual bool Collides(PhysVector3& collisionPoint, const SphereCollider& other) const = 0;

	Matrix4 transform;

	virtual ~Collider() {}
};

