#pragma once
#include <glm/glm.hpp>
#include <Game Engine/SpriteBatch.h>

const float AGENT_WIDTH = 60.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Zombie;
class Human;

class Agent
{
	public:
		Agent();
		virtual ~Agent();
		virtual void Update(const std::vector<std::string>& levelData,
			std::vector<Human*>& humans,
			std::vector<Zombie*>& zombies) = 0;
		bool CollideWithLevel(const std::vector<std::string>& levelData);
		bool CollideWithAgent(Agent* agent);
		void Draw(GameEngine::SpriteBatch& _spriteBatch);
		bool ApplyDamage(float damage);
		glm::vec2 GetPosition() const { return _position; }
	protected:
		void CheckTilePosition(const std::vector<std::string>& levelData,
			std::vector<glm::vec2>& collidingTilePositions,
			float x,
			float y);
		void CollideWithTile(glm::vec2 tilePos);

		glm::vec2 _position;
		GameEngine::Color _color;
		float _speed;
		float _health;		
};

