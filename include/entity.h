#pragma once

#include <raylib.h>

#include "maths_toolbox.h"

class EntityManager;

class Entity
{
	protected:
		float m_rotationSpeed = 0.f;
		float m_translationSpeed = 0.f;

		Rectangle m_srcRect = { 0.f, 0.f, 0.f, 0.f };

		void stayInScreen();
		virtual void move(float deltaTime) = 0;
		virtual void rotate(float deltaTime) = 0;

		Vector2D getRandomPosition();
		Vector2D getInScreenDirection(Vector2D target);

	public:
		bool m_destroyed = false;

		float m_size = 1.f;

		Vector2D m_acceleration;
		Vector2D m_speed;

		Referential2D m_referential;

		Color m_color = WHITE;

		Entity() = default;
		Entity(const Referential2D& referential);
		virtual ~Entity() = default;
		
		virtual void update(float deltaTime) = 0;
		void draw(const Texture2D&) const;
		virtual void drawDebug() const;

		static EntityManager* entityManager;
		static Rect screenBorder;
		static float gameDifficulty;
};