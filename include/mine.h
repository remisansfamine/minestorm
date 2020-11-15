#pragma once

#include "entity.h"

class Mine : public Entity
{
	protected:
		void move(float) override;
		void rotate(float) override;
		virtual void createCollider(int size = 1) = 0;

	public:
		ConcavePolygon m_collider;

		Mine(const Referential2D& referential);
		void update(float) override;
		void drawDebug() const override;
};