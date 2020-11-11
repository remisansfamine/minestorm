#pragma once

#include "entity.h"

class Mine : public Entity
{
	private:
		void move(float) override;
		void rotate(float) override;

	public:
		Mine(const Vector2D& pos, const Vector2D& dir);
		void update(float) override;
		void drawDebug() override;
};