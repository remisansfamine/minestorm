#include "minelayer.h"

#include "spawn_point.h"

#include "maths_utils.h"

void Minelayer::createCollider(float size)
{
	// Set the collider

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
	m_size = 0.225f;

	m_srcRect = { 512, 0, 256, 256 };

	m_rotationSpeed = 0.35f;

	m_translationSpeed = 60.f * gameDifficulty;

	float i_x = randomNumber(-1.f, 1.f);
	float i_y = randomNumber(-1.f, 1.f);

	m_referential = Referential2D(getRandomPosition(),
								  Vector2D(i_x, i_y));

	m_target = getRandomPosition();

	m_destroyed = true;

	createCollider(m_size);

	m_color = RED;
}

void Minelayer::changeTarget()
{
	m_target = getRandomPosition();

	// Create a new spawn point
	SpawnPoint(m_referential.m_origin, false);
}

void Minelayer::update(float deltaTime)
{
	// Change target if the Minelayer reached its old one
	if (sqrDistance(m_referential.m_origin, m_target) < 10.f)
		changeTarget();

	move(deltaTime);

	rotate(deltaTime);

	stayInScreen();
}

void Minelayer::move(float deltaTime)
{
	m_speed = getInScreenDirection(m_target) * m_translationSpeed;

	m_referential.m_origin += m_speed * deltaTime;
}

void Minelayer::rotate(float deltaTime)
{
	m_referential.rotate(angle(m_speed, m_referential.m_j) * m_rotationSpeed * deltaTime);
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