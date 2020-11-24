#include "player.h"

#include "game.h"
#include "entity_manager.h"

#include "bullet.h"
#include "mine.h"

#include <algorithm>
#include <vector>

#include "maths_utils.h"
#include "intersection.h"

#include "particle.h"

void Player::createCollider(float size)
{
	// Set the collider

	ConvexPolygon firstTriangle;
	firstTriangle.pts =
	{
		{ 0.f, -70.f * size },
		{ -50.f * size, 77.f * size },
		{ 0.f, 66.f * size },
	};

	ConvexPolygon secondTriangle;
	secondTriangle.pts =
	{
		{ 0.f, 66.f * size },
		{ 50.f * size, 77.f * size },
		{ 0.f, -70.f * size },
	};

	m_collider.polygon = { firstTriangle, secondTriangle };

	m_shootCooldown = m_fireRate;
}

Player::Player(int index, const Input& input, const Referential2D& referential,
	Color color)
	: m_input(input), Entity(referential)
{
	m_size = 0.225f;

	m_srcRect = { 0, 0, 256, 256 };

	m_rotationSpeed = 2.5f;

	m_translationSpeed = 10000.f;

	m_color = color;

	createCollider(m_size);

	entityManager->m_players.push_back(*this);
}

void Player::update(float deltaTime)
{
	m_shootCooldown -= deltaTime;

	if (IsKeyPressed(m_input.m_randomPos1) || IsKeyPressed(m_input.m_randomPos2))
		randomTeleport();

	if (IsKeyDown(m_input.m_shoot) && entityManager && m_shootCooldown <= 0)
		shoot();

	int yAxis = IsKeyDown(m_input.m_right) - IsKeyDown(m_input.m_left);

	if (yAxis)
		rotate(yAxis * deltaTime);

	move(deltaTime);

	checkCollisionMine();
}

void Player::checkCollisionMine()
{
	// Check the collision with each mine
	ConcavePolygon playerGlobal = m_referential.concaveToGlobal(m_collider);

	playerGlobal.getAABB();

	for (Mine* mine : entityManager->m_mines)
	{
		if (!mine || mine->m_destroyed)
			continue;

		ConcavePolygon mineGlobal = mine->m_referential.concaveToGlobal(mine->m_collider);

		mineGlobal.getAABB();

		if (intersect(playerGlobal, mineGlobal))
		{
			// Hurt the player and destroy the mine if there is a collision

			hurt();

			mine->atDestroy();

			return;
		}
	}
}

void Player::shoot()
{
	m_shootCooldown = m_fireRate;
	Bullet(m_referential, m_color, this);
}

void Player::randomTeleport()
{
	// Draw teleportation particles
	for (int i = 0; i < 15; i++)
		Particle(m_referential, 0.005f, WHITE, randomVector() * 50.f, true);

	bool isValid = true;
	float x, y;

	// Get a valid position where there is no mine by projecting the player collider at a random position
	// And checking if it collides with a mine

	do
	{
		isValid = true;

		x = (float)rand() / (float)RAND_MAX * screenBorder.halfWidth * 2.f;
		y = (float)rand() / (float)RAND_MAX * screenBorder.halfHeight * 2.f;

		Referential2D newRef = m_referential;

		newRef.m_origin = Vector2D(x, y);

		ConcavePolygon playerGlobal = newRef.concaveToGlobal(m_collider);

		playerGlobal.getAABB();

		for (Mine* mine : entityManager->m_mines)
		{
			ConcavePolygon mineGlobal = mine->m_referential.concaveToGlobal(mine->m_collider);

			mineGlobal.getAABB();

			if (intersect(playerGlobal.getAABB(), mineGlobal.getAABB()))
				isValid = false;
		}
	} while (!isValid);

	m_referential.m_origin = Vector2D(x, y);

	// Draw teleportation particles
	for (int i = 0; i < 15; i++)
		Particle(m_referential, 0.005f, WHITE, randomVector() * 50.f, true);
}

Vector2D Player::getAcceleration()
{
	// If the input is pressed set the acceleration with the direction vector
	if (IsKeyDown(m_input.m_forward))
	{
		// Set acceleration in front of the spaceship

		// Create thrust particles
		for (int i = 0; i < 3; i++)
			Particle(m_referential, 0.01f, WHITE, randomVector() * 2.f);

		return -m_referential.m_j / m_mass * m_translationSpeed;
	}
	
	return Vector2D();
}

void Player::move(float deltaTime)
{
	m_acceleration = getAcceleration();

	m_speed += m_acceleration * deltaTime;

	// Clamp speed magnitude and speed.y
	{
		Vector2D localSpeed = m_referential.vectorGlobalToLocal(m_speed);

		// Clamping the speed with a maximum speed and adding friction
		float magnitude = min(localSpeed.magnitude(), m_maxSpeed) * pow(m_friction, deltaTime);

		// Avoid a negative speed
		localSpeed.y = min(0, localSpeed.y);

		m_speed = m_referential.vectorLocalToGlobal(localSpeed.normalized() * magnitude);
	}

	// Rotate the speed vector to the direction vector, to let the player drift
	m_speed.rotate((1 - m_kDrift) * angle(m_speed, -m_referential.m_j) * deltaTime);

	m_referential.m_origin += m_speed * deltaTime;

	stayInScreen();
}

void Player::rotate(float value)
{
	// Rotate the entiere referential
	m_referential.rotate(value * m_rotationSpeed);
}

void Player::drawDebug() const
{
	Entity::drawDebug();

	ConcavePolygon polygonGlobal = m_referential.concaveToGlobal(m_collider);

	Rect concaveAABB = polygonGlobal.getAABB();

	concaveAABB.drawDebug();

	for (const ConvexPolygon& polygon : polygonGlobal.polygon)
		polygon.drawDebug();
}

void Player::hurt()
{
	// Create death particles
	for (int i = 0; i < 2; i++)
		Particle(m_referential, 0.005f, m_color, randomVector() * 50.f, true);

	// Decrementing the life of the player
	if (--m_life <= 0)
	{
		m_destroyed = true;

		// Create death particles
		for (int i = 0; i < 8; i++)
			Particle(m_referential, 0.005f, m_color, randomVector() * 50.f, true);

		// Checking if all player are dead to change the Game State
		if (std::count_if(entityManager->m_players.begin(),
						  entityManager->m_players.end(),
						  [](const Player& p) 
						  { return !p.m_destroyed; }) == 0)
			Game::m_gameState = GameState::GAMEOVER;
	}
}