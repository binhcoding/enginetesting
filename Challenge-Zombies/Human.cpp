#include "Human.h"


Human::Human()
{

}


Human::~Human()
{

}

void Human::Update()
{
	// if you're being chased
	// run in a random direction away from the zombie
}

void Human::SetChase(bool beingChased)
{
	_beingChased = beingChased;
}
