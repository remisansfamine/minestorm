#include "minelayer.h"

#include "spawn_point.h"

#include <iostream>

void Minelayer::createCollider(float size)
{
	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ 0.f,		  -32.f * size },
		{-34.f * size,-12.f * size },
		{ 34.f * size,-12.f * size },
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{-108.f * size,-12.f * size },
		{-108.f * size, 12.f * size },
		{-128.f * size, 34.f * size },
	};

	ConvexPolygon thirdTriangle;
	thirdTriangle.pts =
	{
		{ 108.f * size, 12.f * size },
		{ 108.f * size,-12.f * size },
		{ 128.f * size, 34.f * size },
	};

	ConvexPolygon base;
	base.pts =
	{
		{-108.f * size,-12.f * size },
		{-108.f * size, 12.f * size },
		{ 108.f * size, 12.f * size },
		{ 108.f * size,-12.f * size },
	};

	m_collider.polygon = { firstTriangle, secondTriangle, thirdTriangle, base };
}

Minelayer::Minelayer()
{
	m_size = 0.5f;

	m_srcRect = { 512, 0, 256, 256 };

	m_rotationSpeed = 0.35f;

	m_translationSpeed = 60.f;

	float x = randomNumber(-screenBorder.halfWidth, screenBorder.halfWidth);
	float y = randomNumber(-screenBorder.halfHeight, screenBorder.halfHeight);

	float i_x = randomNumber(-1.f, 1.f);
	float i_y = randomNumber(-1.f, 1.f);

	m_referential = Referential2D(Vector2D(x, y),
								  Vector2D(i_x, i_y));

	m_target = { screenBorder.halfWidth, screenBorder.halfHeight };

	createCollider(0.15f * m_size + 0.15f);

	m_color = RED;
}

Vector2D Minelayer::getTarget()
{
	return screenBorder.pt + Vector2D(randomNumber(-screenBorder.halfWidth, screenBorder.halfWidth),
									  randomNumber(-screenBorder.halfHeight, screenBorder.halfHeight));
}

void Minelayer::update(float deltaTime)
{
	if (sqrDistance(m_referential.m_origin, m_target) < 10.f)
	{
		m_target = getTarget();
		SpawnPoint(m_referential.m_origin, true);
	}

	move(deltaTime);

	rotate(deltaTime);

	stayInScreen();
}

void Minelayer::move(float deltaTime)
{
	Vector2D m_direction = (m_target - m_referential.m_origin);

	m_direction.x *= sign(screenBorder.halfWidth - abs(m_direction.x));

	m_direction.y *= sign(screenBorder.halfHeight - abs(m_direction.y));

	m_speed = m_direction.normalized() * m_translationSpeed;

	m_referential.m_origin += m_speed * deltaTime;
}

void Minelayer::rotate(float deltaTime)
{
	m_referential.rotate(angle(m_speed, m_referential.m_j) * m_rotationSpeed * deltaTime );
}

void Minelayer::drawDebug() const
{
	Entity::drawDebug();

	ConcavePolygon polygonGlobal = m_referential.concaveToGlobal(m_collider);

	Rect concaveAABB = polygonGlobal.getAABB();

	concaveAABB.drawDebug();

	for (const ConvexPolygon& polygon : polygonGlobal.polygon)
		polygon.drawDebug();
}