#pragma once

#include <raylib.h>

#include "math_toolbox.h"

class EntityManager;

class Entity
{
	public:
		Entity(const Vector2D& pos, const Vector2D& dir);
		float m_size = 0.5f;
		Vector2D m_acceleration;
		Vector2D m_speed;
		Referential2D m_referential;

		virtual void update(float deltaTime) = 0;
		void draw(const Texture2D&);
		virtual void drawDebug();

		static EntityManager* m_entityManager;

	protected:
		float m_maxSpeed = 250.f;
		float m_friction = 0.6f;
		float m_rotationSpeed = 100.f;
		float m_translationSpeed = 0.f;
		Color m_color = WHITE;
		Rectangle m_srcRect = { 0.f, 0.f, 0.f, 0.f };

		void stayInScreen();
		virtual void move(float deltaTime) = 0;
		virtual void rotate(float deltaTime) = 0;

};