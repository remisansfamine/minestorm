#pragma once

#include "mine.h"

class MagneticFireballMine : public Mine
{
	private:
		void createCollider(int size = 1) override;

	public:
		MagneticFireballMine(const Referential2D& referential);
};