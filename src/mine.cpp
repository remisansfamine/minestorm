#include "mine.h"

#include <iostream>

#include "entity_manager.h"

Mine::Mine(const Vector2D& pos, const Vector2D& dir)
	: Entity(pos, dir)
{
	m_entityManager->m_mine.push_back(this);
}

void Mine::update(float deltaTime)
{
	move(deltaTime);
	rotate(deltaTime);
}

void Mine::move(float deltaTime)
{
	m_referential.m_origin += m_speed * deltaTime;
}

void Mine::rotate(float deltaTime)
{
	m_referential.rotate(deltaTime * m_rotationSpeed);
}

void Mine::drawDebug()
{
	Entity::drawDebug();
}