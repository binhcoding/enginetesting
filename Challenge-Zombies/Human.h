#pragma once
#include "Agent.h"
class Human : public Agent
{
	public:
	Human();
	virtual ~Human();
	void Init(float speed, glm::vec2 position);
	virtual void Update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	private:
	glm::vec2 _direction;
	int _frames;
};

