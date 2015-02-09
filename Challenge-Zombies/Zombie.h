#pragma once
#include "Agent.h"
class Zombie : public Agent
{
	public:
	Zombie();
	~Zombie();
	void Init(float speed, glm::vec2 position);
	void Update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);
	private:
	Human* GetNearestHuman(std::vector<Human*>& humans);
};

