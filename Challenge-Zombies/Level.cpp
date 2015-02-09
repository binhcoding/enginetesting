#include "Level.h"
#include <fstream>
#include <Game Engine/Errors.h>
#include <Game Engine/ResourceManager.h>
#include <Game Engine/Vertex.h>
#include <Game Engine/GLTexture.h>
#include <iostream>
#include <glm/glm.hpp>

Level::Level(const std::string& levelPath)
{
	std::ifstream inputFile(levelPath);
	if (inputFile.fail())
	{
		GameEngine::FatalError("File failed to open: " + levelPath);
	}

	// get the first line
	std::string firstLine;
	getline(inputFile, firstLine);
	firstLine = firstLine.substr(8, firstLine.length());
	_humanCount = std::stoi(firstLine);
	while (getline(inputFile, firstLine))
	{
		_levelData.push_back(firstLine);
	}

	GameEngine::Color color;
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	_spriteBatch.Init();
	_spriteBatch.Begin();

	// first  [] is x
	// second [] is y
	for (int y = 0; y < _levelData.size(); y++)
	{
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			char currentChar = _levelData[y][x];
			glm::vec4 positionAndSize = glm::vec4(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);
			switch (currentChar)
			{
				// Textures/circle.png | glass.png | light_bricks.png | red_bricks.png
				case 'R':
				{
					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/red_bricks.png");
					_spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
				}
				break;
				case 'G':
				{
					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/glass.png");
					_spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);

				}
				break;
				case 'B':
				{
					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/red_bricks.png");
					_spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
				}
				break;
				case 'Z':
				{
					_levelData[y][x] = '.';
					_zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
				}
				break;
				case '@': // player spawn
				{
					_levelData[y][x] = '.';
					_playerStartPosition.x = x * TILE_WIDTH;
					_playerStartPosition.y = y * TILE_WIDTH;
				}
				break;
				case 'L':
				{
					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/light_bricks.png");
					_spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
				}
				break;
				default:
					break;
			}
		}
	}

	_spriteBatch.End();
}

Level::~Level()
{
}

void Level::Draw()
{
	_spriteBatch.RenderBatches();
}