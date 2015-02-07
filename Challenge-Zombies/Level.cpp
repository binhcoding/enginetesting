#include "Level.h"
#include <fstream>
#include <Game Engine/Errors.h>
#include <Game Engine/ResourceManager.h>
#include <Game Engine/Vertex.h>
#include <Game Engine/GLTexture.h>
#include <iostream>
#include <glm/glm.hpp>

Level::Level()
{
}

Level::~Level()
{
}

void Level::LoadLevel(const std::string& levelPath)
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

	// first  [] is x
	// second [] is y
	for (int i = 0; i < _levelData.size(); i++)
	{
		for (int j = 0; j < _levelData[i].size(); j++)
		{
			char currentChar = _levelData[i][j];
			switch (currentChar)
			{
				// Textures/circle.png | glass.png | light_bricks.png | red_bricks.png
				case 'R':
				{

					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/red_bricks.png");
					GameEngine::Color color;
					color.SetColor(255, 255, 255, 255);
					glm::vec4 positionAndSize = glm::vec4(j * 32, i * 32, 32, 32);
					Tile* tile = new Tile;
					tile->collidable = true;
					tile->color = color;
					tile->positionAndSize = positionAndSize;
					tile->texture = texture;
					_tileMap[i][j] = tile;

					//spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
				}
				break;
				case 'G':
				{
					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/glass.png");
					GameEngine::Color color;
					color.SetColor(255, 255, 255, 255);
					glm::vec4 positionAndSize = glm::vec4(j * 32, i * 32, 32, 32);
					//spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
					Tile* tile = new Tile;
					tile->collidable = true;
					tile->color = color;
					tile->positionAndSize = positionAndSize;
					tile->texture = texture;
					_tileMap[i][j] = tile;

				}
				break;
				case 'B':
				{
					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/red_bricks.png");
					GameEngine::Color color;
					color.SetColor(0, 0, 255, 255);
					glm::vec4 positionAndSize = glm::vec4(j * 32, i * 32, 32, 32);
					//spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
					Tile* tile = new Tile;
					tile->collidable = true;
					tile->color = color;
					tile->positionAndSize = positionAndSize;
					tile->texture = texture;
					_tileMap[i][j] = tile;
				}
				break;
				case 'Z':
				{
					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/circle.png");
					GameEngine::Color color;
					color.SetColor(165, 42, 42, 255);
					glm::vec4 positionAndSize = glm::vec4(j * 32, i * 32, 32, 32);
					//spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
					Tile* tile = new Tile;
					tile->collidable = true;
					tile->color = color;
					tile->positionAndSize = positionAndSize;
					tile->texture = texture;
					_tileMap[i][j] = tile;
				}
				break;
				case '@': // player spawn
				{
					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/circle.png");
					GameEngine::Color color;
					color.SetColor(255, 255, 0, 255);
					glm::vec4 positionAndSize = glm::vec4(j * 32, i * 32, 32, 32);
					//spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
					Tile* tile = new Tile;
					tile->collidable = true;
					tile->color = color;
					tile->positionAndSize = positionAndSize;
					tile->texture = texture;
					_tileMap[i][j] = tile;
				}
				break;
				case 'L':
				{
					GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/light_bricks.png");
					GameEngine::Color color;
					color.SetColor(255, 255, 255, 255);
					glm::vec4 positionAndSize = glm::vec4(j * 32, i * 32, 32, 32);
					//spriteBatch.Draw(positionAndSize, uv, texture.id, 0.0f, color);
					Tile* tile = new Tile;
					tile->collidable = true;
					tile->color = color;
					tile->positionAndSize = positionAndSize;
					tile->texture = texture;
					_tileMap[i][j] = tile;
				}
				break;
				default:
					Tile* tile = new Tile{};
					tile->collidable = false;
					_tileMap[i][j] = tile;
					break;
			}
		}
	}
}

void Level::Draw(GameEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _columns; j++)
		{
			if (_tileMap[i][j]->texture.id != 0) // thar is a texture, render this space
			{
				spriteBatch.Draw(_tileMap[i][j]->positionAndSize, uv, _tileMap[i][j]->texture.id, 0.0f, _tileMap[i][j]->color);
			}
		}
	}
}

Tile* Level::GetNorth(int x, int y)
{
	if (ErrorCheck(x, y))
		return nullptr;
	if (x > 0)
		return _tileMap[x - 1][y];
	return nullptr;
}

Tile* Level::GetWest(int x, int y)
{
	if (ErrorCheck(x, y))
		return nullptr;
	if (y > 0)
		return _tileMap[x][y - 1];
	return nullptr;
}

Tile* Level::GetEast(int x, int y)
{
	if (ErrorCheck(x, y))
		return nullptr;
	if (y < 113)
		return _tileMap[x][y + 1];
	return nullptr;
}

Tile* Level::GetSouth(int x, int y)
{
	if (ErrorCheck(x, y))
		return nullptr;
	if (x < 33)
		return _tileMap[x + 1][y];
	return nullptr;
}

bool Level::ErrorCheck(int x, int y)
{
	if (x >= 33)
		return true;
	if (y >= 113)
		return true;
	return false;
}
