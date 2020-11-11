#include "player.h"

#include <raylib.h>

#include "entity_manager.h"

Player::Player(int index, const Input& input, const Vector2D& pos, const Vector2D& dir)
	: m_input(input), Entity(pos, dir)
{
	m_srcRect = { 0, 0, 256, 256 };

	m_translationSpeed = 10000.f;

	m_color = index ? LIME : BLUE;

	m_entityManager->m_player.push_back(*this);
}

void Player::update(float deltaTime)
{
	if (IsKeyPressed(m_input.m_randomPos1) || IsKeyPressed(m_input.m_randomPos2))
		randomTeleport();

	if (IsKeyPressed(m_input.m_shoot) && m_entityManager)
		Projectile(m_referential.m_origin, m_referential.m_i, m_color);

	int yAxis = IsKeyDown(m_input.m_right) - IsKeyDown(m_input.m_left);

	if (yAxis)
		rotate(yAxis * deltaTime);

	move(deltaTime);
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

void Player::drawDebug()
{
	Entity::drawDebug();
}