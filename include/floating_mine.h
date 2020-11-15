#pragma once

#include "mine.h"

#include "math_toolbox.h"

class FloatingMine : public Mine
{
	private:
		void createCollider(int size = 1) override;

	public:
		FloatingMine(const Referential2D& referential);
};