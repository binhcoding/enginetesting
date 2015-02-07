#pragma once
#include "Agent.h"
class Human : public Agent
{
	public:
	Human();
	~Human();
	void Update();
	void SetChase(bool beingChased);
	private:
	bool _beingChased;
};

