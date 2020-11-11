#pragma once

#include "mine.h"

class MagneticMine : public Mine
{
	public:
		MagneticMine(const Vector2D& pos, const Vector2D& dir);
};