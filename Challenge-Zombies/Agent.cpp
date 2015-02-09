#include "Agent.h"
#include "Level.h"
#include <Game Engine/ResourceManager.h>
#include <algorithm>

Agent::Agent()
{
}


Agent::~Agent()
{
}

bool Agent::CollideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collidingTilePositions;

	// bounding box, check corners
	CheckTilePosition(levelData, collidingTilePositions, _position.x, _position.y);
	CheckTilePosition(levelData, collidingTilePositions, _position.x + AGENT_WIDTH, _position.y);
	CheckTilePosition(levelData, collidingTilePositions, _position.x, _position.y + AGENT_WIDTH);
	CheckTilePosition(levelData, collidingTilePositions, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

	if (collidingTilePositions.size() == 0)
		return false;

	// do the collision
	for (int i = 0; i < collidingTilePositions.size(); i++)
	{
		CollideWithTile(collidingTilePositions[i]);
	}
	return true;
}

bool Agent::CollideWithAgent(Agent* agent)
{
	//circular collision
	// minimum distance before there is a collision
	const float MIN_DISTANCE = AGENT_RADIUS * 2.0f;

	// center position of this agent
	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
	// center position of the target agent
	glm::vec2 centerPosB = agent->GetPosition() + glm::vec2(AGENT_RADIUS);

	// distance vector between the two agents
	glm::vec2 distVec = centerPosA - centerPosB;

	// length of the distance vector
	float distance = glm::length(distVec);

	// depth of the collision
	float collisionDepth = MIN_DISTANCE - distance;

	// if the collision depth > 0 then we did collide
	if (collisionDepth > 0)
	{
		// get the direction times the collision depth so we can push them away from each other
		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;

		// push them in opposite directions
		_position += collisionDepthVec / 2.0f;
		agent->_position -= collisionDepthVec / 2.0f;
		return true;
	}
	return false;
}

void Agent::CheckTilePosition(const std::vector<std::string>& levelData,
	std::vector<glm::vec2>& collidingTilePositions,
	float x,
	float y)
{
	// get the position of this corner in grid space
	glm::vec2 gridPos = glm::vec2(floor(x / (float)TILE_WIDTH), floor(y / (float)TILE_WIDTH));

	// outside the world
	if (gridPos.x < 0 || gridPos.x >= levelData[0].size() ||
		gridPos.y < 0 || gridPos.y >= levelData.size())
		return;

	// not an air tile, trigger collision
	if (levelData[gridPos.y][gridPos.x] != '.')
	{
		collidingTilePositions.push_back(gridPos *(float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

void Agent::Draw(GameEngine::SpriteBatch& _spriteBatch)
{
	static int textureId = GameEngine::ResourceManager::GetTexture("Textures/circle.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	_spriteBatch.Draw(destRect, uvRect, textureId, 0.0f, _color);
}

bool Agent::ApplyDamage(float damage)
{
	_health -= damage;
	if (_health <= 0)
	{
		return true;
	}
	return false;
}

void Agent::CollideWithTile(glm::vec2 tilePos)
{
	//axis aligned bounding box
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	// min distance before collision
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

	glm::vec2 centerAgentPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerAgentPos - tilePos;

	// depth of collision
	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	if (xDepth > 0 && yDepth > 0)
	{
		// check with collision depth is less
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f))
		{
			//x collision depth, push in x direction
			if (distVec.x < 0)
			{
				_position.x -= xDepth;
			}
			else
			{
				_position.x += xDepth;
			}
		}
		else
		{
			// y collision depth, push in y direction
			if (distVec.y < 0)
			{
				_position.y -= yDepth;
			}
			else
			{
				_position.y += yDepth;
			}
		}
	}
}