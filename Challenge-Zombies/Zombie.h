#pragma once
#include "Agent.h"
#include "Human.h"
class Zombie : public Agent
{
	public:
	Zombie();
	~Zombie();
	void Chase(Human& target);
	void Update();
	private:
	Human* _target;
	float _leashRange = 5.0f;

};

