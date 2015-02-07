#pragma once
#include "Tile.h"

enum class Directions { NORTH, EAST, SOUTH, WEST};

class Agent
{
	public:
		Agent();
		~Agent();
		void Run();
		void Walk();
		Tile* TileOccupied;
		bool CanMove(Directions direction);
		virtual void Update() = 0;
	protected:
		bool _isRunning;
		float _speed;
		
};

