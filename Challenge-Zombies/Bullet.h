#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <Game Engine/SpriteBatch.h>
#include "Agent.h"

class Human;
class Zombie;

const float BULLET_RADIUS = 5.0f;

class Bullet
{
	public:
	Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed);
	~Bullet();

	bool Update(const std::vector<std::string>& levelData);

	void Draw(GameEngine::SpriteBatch& spriteBatch);

	bool CollideWithAgent(Agent* agent);

	float GetDamage() const { return _damage; }
	private:
	bool CollideWithWorld(const std::vector<std::string>& levelData);

	glm::vec2 _position;
	glm::vec2 _direction;
	float _damage;
	float _speed;
};

