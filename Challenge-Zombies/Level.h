#pragma once
#include <string>
#include <vector>
#include <Game Engine/SpriteBatch.h>
#include "Tile.h"

class Level
{
	public:
		Level();
		~Level();
		void LoadLevel(const std::string& levelPath);
		void Draw(GameEngine::SpriteBatch& spriteBatch);
	private:
		Tile* GetNorth(int x, int y);
		Tile* GetWest(int x, int y);
		Tile* GetEast(int x, int y);
		Tile* GetSouth(int x, int y);
		bool ErrorCheck(int x, int y);
		std::vector<std::string> _levelData;
		int _humanCount;
		static const int _rows = 32;
		static const int _columns = 112;
		Tile* _tileMap[_rows][_columns];
};

