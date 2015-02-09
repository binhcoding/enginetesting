#include "Zombie.h"
#include <glm/glm.hpp>
#include "Human.h"

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::Init(float speed, glm::vec2 position)
{
	_health = 150;
	_speed = speed;
	_position = position;
	_color.r = 0;
	_color.g = 160;
	_color.b = 0;
	_color.a = 255;
}

void Zombie::Update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies)
{
	Human* closestHuman = GetNearestHuman(humans);

	if (closestHuman != nullptr)
	{
		glm::vec2 direction = glm::normalize(closestHuman->GetPosition() - _position);
		_position += direction * _speed;
	}

	CollideWithLevel(levelData);
}

Human* Zombie::GetNearestHuman(std::vector<Human*>& humans)
{
	Human* closestHuman = nullptr;
	float smallestDistance = 999999.0f;
	for (int i = 0; i < humans.size(); i++)
	{
		glm::vec2 distVect = humans[i]->GetPosition() - _position;
		float distance = glm::length(distVect);
		
		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}


	return closestHuman;
}