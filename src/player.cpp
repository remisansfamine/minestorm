#include "player.h"

#include <raylib.h>

#include "entity_manager.h"

#include "bullet.h"

#include "mine.h"

#include <iostream>

void Player::createCollider()
{
	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ 0.f, -70.f * m_size },
		{ -50.f * m_size, 77.f * m_size },
		{ 0.f, 66.f * m_size },
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ 0.f, 66.f * 0.5f },
		{ 50.f * 0.5f, 77.f * 0.5f },
		{ 0.f, -70.f * 0.5f },
	};

	m_collider.polygon = { firstTriangle, secondTriangle };
}

Player::Player(int index, const Input& input, const Referential2D& referential)
	: m_input(input), Entity(referential)
{
	m_srcRect = { 0, 0, 256, 256 };

	m_translationSpeed = 10000.f;

	m_color = index ? LIME : BLUE;

	createCollider();

	m_entityManager->m_player.push_back(*this);
}

void Player::update(float deltaTime)
{
	if (IsKeyPressed(m_input.m_randomPos1) || IsKeyPressed(m_input.m_randomPos2))
		randomTeleport();

	if (IsKeyPressed(m_input.m_shoot) && m_entityManager)
		new Bullet(Referential2D(m_referential.m_origin, m_referential.m_i), m_color);

	int yAxis = IsKeyDown(m_input.m_right) - IsKeyDown(m_input.m_left);

	if (yAxis)
		rotate(yAxis * deltaTime);

	move(deltaTime);

	ConcavePolygon playerPolygonGlobal = m_referential.concaveToGlobal(m_collider);
	Rect playerAABB = playerPolygonGlobal.getAABB();

	for (Mine* mine : m_entityManager->m_mine)
	{
		if (!mine)
			continue;

		ConcavePolygon minePolygonGlobal = mine->m_referential.concaveToGlobal(mine->m_collider);
		Rect mineAABB = minePolygonGlobal.getAABB();

		if (intersect(playerAABB, mineAABB))
		{
			for (const ConvexPolygon& playerPolygon : playerPolygonGlobal.polygon)
			{
				playerAABB = playerPolygon.getAABB();

				for (const ConvexPolygon& minePolygon : minePolygonGlobal.polygon)
				{
					mineAABB = minePolygon.getAABB();

					if (intersect(playerAABB, mineAABB))
					{
						if (intersect(playerPolygon, minePolygon))
						{
							m_shouldBeDestroyed = mine->m_shouldBeDestroyed = true;
							break;
						}
					}
				}
			}
		}
	}
}

void Player::randomTeleport()
{
	Image screenData = GetScreenData();

	m_referential.m_origin.x = (float)rand() / (float)RAND_MAX * screenData.width;
	m_referential.m_origin.y = (float)rand() / (float)RAND_MAX * screenData.height;
}

void Player::move(float deltaTime)
{
	if (IsKeyDown(m_input.m_forward))
		m_thrust = -m_referential.m_j;
	else
		m_thrust = Vector2D(0.f, 0.f);

	m_acceleration = m_thrust / m_mass * m_translationSpeed;

	m_speed += m_acceleration * deltaTime;

	// Clamp speed magnitude and y speed
	{
		Vector2D localSpeed = m_referential.vectorGlobalToLocal(m_speed);

		float magnitude = min(localSpeed.magnitude(), m_maxSpeed) * pow(m_friction, deltaTime);

		// TODO: Change sign of y
		localSpeed.y = min(0, localSpeed.y); // Should put max because y is opposed

		m_speed = m_referential.vectorLocalToGlobal(localSpeed.normalized() * magnitude);
	}
	
	// Rotate the speed vector to let the player drift
	m_speed.rotate((1 - m_kDrift) * angle(m_speed, -m_referential.m_j) * M_PI / 180.f);

	m_referential.m_origin += m_speed * deltaTime;

	stayInScreen();
}

void Player::rotate(float value)
{
	m_referential.rotate(value * m_rotationSpeed);
}

void Player::drawDebug() const
{
	Entity::drawDebug();

	ConcavePolygon polygonGlobal = m_referential.concaveToGlobal(m_collider);

	Rect concaveAABB = polygonGlobal.getAABB();

	DrawRectangleLines(concaveAABB.pt.x - concaveAABB.halfWidth,
		concaveAABB.pt.y - concaveAABB.halfHeight,
		concaveAABB.halfWidth * 2.f,
		concaveAABB.halfHeight * 2.f,
		PINK);

	for (const ConvexPolygon& polygon : polygonGlobal.polygon)
	{
		Rect  convexAABB = polygon.getAABB();

		DrawRectangleLines(convexAABB.pt.x - convexAABB.halfWidth,
						   convexAABB.pt.y - convexAABB.halfHeight,
						   convexAABB.halfWidth * 2.f,
						   convexAABB.halfHeight * 2.f,
						   BLUE);

		for (unsigned int i = 0; i < polygon.pts.size(); i++)
		{
			unsigned int j = (i + 1) % polygon.pts.size();

			Vector2D point0 = polygon.pts[i];
			Vector2D point1 = polygon.pts[j];

			DrawCircle(point0.x, point0.y, 2, BLACK);
			DrawLine(point0.x, point0.y, point1.x, point1.y, ORANGE);
		}
	}
}