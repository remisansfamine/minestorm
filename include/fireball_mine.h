#pragma once

#include "mine.h"

class FireballMine : public Mine
{
	private:
		void createCollider(int size = 1) override;

	public:
		FireballMine(const Referential2D& referential);
};