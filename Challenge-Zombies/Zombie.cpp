#include "Zombie.h"
#include <glm/glm.hpp>

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::Chase(Human& target)
{
	_target = &target;
}

void Zombie::Update()
{
	if (_target == nullptr)
		return;
	// what if the target manages to get away from you
	glm::vec2 myPosition(TileOccupied->positionAndSize.x, TileOccupied->positionAndSize.y);
	glm::vec2 targetPosition(_target->TileOccupied->positionAndSize.x, _target->TileOccupied->positionAndSize.y);
	if (glm::distance(myPosition, targetPosition) > _leashRange)
	{
		_target == nullptr;
		return;
	}
	glm::vec2 direction = myPosition - targetPosition;
	direction = glm::normalize(direction);
	myPosition += direction * _speed;
	// TODO: convert direction into a cardinal direction to check if its legal to move in that direction
	TileOccupied->positionAndSize.x = myPosition.x;
	TileOccupied->positionAndSize.y = myPosition.y;
}