#include "Bullet.h"
#include <Game Engine/ResourceManager.h>
#include "Level.h"


Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
_position(position), _direction(direction), _damage(damage), _speed(speed)

{

}


Bullet::~Bullet()
{

}

bool Bullet::Update(const std::vector<std::string>& levelData)
{
	_position += _direction * _speed;
	return CollideWithWorld(levelData);
}

void Bullet::Draw(GameEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 destRect(_position.x + BULLET_RADIUS, _position.y + BULLET_RADIUS, BULLET_RADIUS * 2, BULLET_RADIUS * 2);
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	GameEngine::ColorRGBA8 color;
	color.r = 75;
	color.g = 75;
	color.b = 75;
	color.a = 255;

	spriteBatch.Draw(destRect, uvRect, GameEngine::ResourceManager::GetTexture("Textures/circle.png").id, 0.0f, color);
}

bool Bullet::CollideWithAgent(Agent* agent)
{
	//circular collision
	// minimum distance before there is a collision
	const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

	// center position of this agent
	glm::vec2 centerPosA = _position;
	// center position of the target agent
	glm::vec2 centerPosB = agent->GetPosition() + glm::vec2(AGENT_RADIUS);

	// distance vector between the two agents
	glm::vec2 distVec = centerPosA - centerPosB;

	// length of the distance vector
	float distance = glm::length(distVec);

	// depth of the collision
	float collisionDepth = MIN_DISTANCE - distance;

	// if the collision depth > 0 then we did collide
	if (collisionDepth > 0)
	{
		return true;
	}
	return false;
}

bool Bullet::CollideWithWorld(const std::vector<std::string>& levelData)
{
	glm::ivec2 gridPosition;
	gridPosition.x = floor(_position.x / (float)TILE_WIDTH);
	gridPosition.y = floor(_position.y / (float)TILE_WIDTH);

	if (gridPosition.x < 0 || gridPosition.x >= levelData[0].size() ||
		gridPosition.y < 0 || gridPosition.y >= levelData.size())
		return true;

	return (levelData[gridPosition.y][gridPosition.x] != '.');	
}