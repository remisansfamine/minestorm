#pragma once

#include "mine.h"

class MagneticMine : public Mine
{
	private:
		void createCollider(int size = 1) override;

	public:
		MagneticMine(const Referential2D& referential);
};