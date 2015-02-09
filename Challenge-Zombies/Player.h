#pragma once
#include "Human.h"
#include <Game Engine/InputManager.h>
#include <Game Engine/Camera2D.h>
#include "Bullet.h"

class Gun;

class Player :
	public Human
{
	public:
		Player();
		~Player();
		void Init(float speed, glm::vec2 position, GameEngine::InputManager* inputManager, GameEngine::Camera2D* camera, std::vector<Bullet>* bullets);
		void Update(const std::vector<std::string>& levelData,
			std::vector<Human*>& humans,
			std::vector<Zombie*>& zombies) ;

		void AddGun(Gun* gun);

	private:
		GameEngine::InputManager* _inputManager;
		std::vector<Gun*> _guns;
		GameEngine::Camera2D* _camera;
		std::vector<Bullet>* _bullets;
		int _currentGunIndex;

};

