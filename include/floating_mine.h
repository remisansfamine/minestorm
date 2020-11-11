#pragma once

#include "mine.h"

class FloatingMine : public Mine
{
	public:
		FloatingMine(const Vector2D& pos, const Vector2D& dir);
};