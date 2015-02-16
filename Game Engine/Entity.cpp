#include "Entity.h"
#include "GameEngine.h"
#include <string>
#include <iostream>

namespace GameEngine
{
	Entity::Entity() : _isInit(false)
	{
		_id = GetRandomId();
	}

	Entity::~Entity()
	{

	}


}