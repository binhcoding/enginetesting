#pragma once
#include <string>
#include <vector>
#include <Game Engine/SpriteBatch.h>

const int TILE_WIDTH = 64;

class Level
{
	public:
		Level(const std::string& levelPath);
		~Level();
		void Draw();

		int GetWidth() const { return _levelData[0].size(); }
		int GetHeight() const { return _levelData.size(); }
		int GetNumHumans() const { return _humanCount; }
		const std::vector<std::string>& GetLevelData() const { return _levelData; }
		glm::vec2 GetPlayerStartPosition() const { return _playerStartPosition; }
		const std::vector<glm::vec2>& GetZombieStartPositions() const { return _zombieStartPositions; }
	private:
		std::vector<std::string> _levelData;
		int _humanCount;
		GameEngine::SpriteBatch _spriteBatch;
		glm::vec2 _playerStartPosition;
		std::vector<glm::vec2> _zombieStartPositions;
};

