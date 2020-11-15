#pragma once

#include "projectile.h"

#include "math_toolbox.h"

class Bullet : public Projectile
{
	public:
		Bullet(const Referential2D& referential, Color color);
};