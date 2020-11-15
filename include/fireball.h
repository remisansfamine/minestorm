#pragma once

#include "projectile.h"

#include "math_toolbox.h"

class Fireball : public Projectile
{
	public:
		Fireball(const Referential2D& referential);
};