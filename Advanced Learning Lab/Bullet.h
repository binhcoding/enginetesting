#pragma once
#include <glm/glm.hpp>
#include <Game Engine/SpriteBatch.h>

class Bullet
{
	public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
	~Bullet();

	void Draw(GameEngine::SpriteBatch& spriteBatch);
	// returns true when out of life
	bool Update();

	private:
	float _speed;
	int _lifeTime;
	glm::vec2 _direction;
	glm::vec2 _position;
};

