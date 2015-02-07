#include "Bullet.h"
#include <Game Engine/ResourceManager.h>
#include <Game Engine/Vertex.h>
#include <Game Engine/GLTexture.h>

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime)
{
	_lifeTime = lifeTime;
	_position = pos;
	_direction = dir;
	_speed = speed;
}


Bullet::~Bullet()
{

}

void Bullet::Draw(GameEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	
	glm::vec4 positionAndSize = glm::vec4(_position.x, _position.y, 30, 30);

	spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
	
}

bool Bullet::Update()
{
	_position += _direction * _speed;
	_lifeTime--;
	if (_lifeTime == 0)
	{
		return true;
	}
	return false;
}