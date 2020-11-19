#pragma once

#include "mine.h"

class Player;

class MagneticFireballMine : public Mine
{
	private:
		Player* m_target = nullptr;

		void createCollider(float size = 1.f) override;
		void getTarget();

	public:
		MagneticFireballMine(int size = 2);

		void atDestroy() override;
		void update(float deltaTime) override;
};