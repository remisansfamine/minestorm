#pragma once

#include "mine.h"

class FloatingMine : public Mine
{
	private:
		void createCollider(float size = 1.f) override;

	public:
		FloatingMine(int size = 2);
		void atDestroy() override;
};