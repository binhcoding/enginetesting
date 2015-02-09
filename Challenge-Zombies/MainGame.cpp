#include "MainGame.h"

#include <Game Engine/GameEngine.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>
#include "Zombie.h"
#include <random>
#include <ctime>
#include <Game Engine/Errors.h>
#include "Gun.h"
const float HUMAN_SPEED = 1.0f;
const float ZOMBIE_SPEED = 1.3f;
const float BULLET_SPEED = 20.0f;

MainGame::MainGame() : _screenWidth(1080), _screenHeight(720), _maxFps(60.0f), _player(nullptr), _numHumansKilled(0), _numZombiesKilled(0)
{
	// Empty
	_camera.Init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
	// IMPLEMENT THIS!
}

void MainGame::Run()
{
	// IMPLEMENT THIS!
	InitSystems();
	GameLoop();
}

void MainGame::InitSystems()
{
	GameEngine::Init();
	_window.Create("Zambies", _screenWidth, _screenHeight, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	InitShaders();
	_spriteBatch.Init();
	_fpsLimiter.Init(_maxFps);


	_level = new Level("Levels/level1.txt");
	_player = new Player();
	_player->Init(4.0f, _level->GetPlayerStartPosition(), &_inputManager, &_camera, &_bullets);
	_humans.push_back(_player);

	std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	std::uniform_int_distribution<int> randomXPosition(2, _level->GetWidth() - 2);
	std::uniform_int_distribution<int> randomYPosition(2, _level->GetHeight() - 2);

	
	// add humans
	for (int i = 0; i < _level->GetNumHumans(); i++)
	{
		_humans.push_back(new Human);
		_humans.back()->Init(HUMAN_SPEED, glm::vec2(randomXPosition(randomEngine) * TILE_WIDTH, randomYPosition(randomEngine) * TILE_WIDTH));
	}
	// add zombies
	const std::vector<glm::vec2>& zombiePositions = _level->GetZombieStartPositions();
	for (int i = 0; i < zombiePositions.size(); i++)
	{
		_zombies.push_back(new Zombie);
		_zombies.back()->Init(ZOMBIE_SPEED, zombiePositions[i]);
	}

	// set up the player guns
	
	_player->AddGun(new Gun("Magnum", 10, 1, 10.0f, 30, BULLET_SPEED));
	_player->AddGun(new Gun("Shotgun", 30, 20, 40.0f, 4, BULLET_SPEED));
	_player->AddGun(new Gun("MP5", 2, 1, 20.0f, 20, BULLET_SPEED));
}

void MainGame::InitShaders()
{
	// Compile our color shader
	_textureProgram.CompileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	_textureProgram.AddAttributes("vertexPosition");
	_textureProgram.AddAttributes("vertexColor");
	_textureProgram.AddAttributes("vertexUV");
	_textureProgram.LinkShaders();
}

void MainGame::GameLoop()
{
	_fpsLimiter.SetMaxFPS(60.0f);
	// IMPLEMENT THIS!
	while (true)
	{
		_fpsLimiter.Begin();
		CheckVictory();
		ProcessInput();
		UpdateAgents();
		UpdateBullets();
		_camera.SetPosition(_player->GetPosition());
		_camera.Update();
		DrawGame();
		_fps = _fpsLimiter.End();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 100)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::UpdateAgents()
{
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->Update(_level->GetLevelData(), _humans, _zombies);
	}


	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->Update(_level->GetLevelData(), _humans, _zombies);
	}

	// zombie collision
	for (int i = 0; i < _zombies.size(); i++)
	{
		for (int j = i + 1; j < _zombies.size(); j++)
		{
			_zombies[i]->CollideWithAgent(_zombies[j]);
		}

		for (int j = 1; j < _humans.size(); j++)
		{
			if (_zombies[i]->CollideWithAgent(_humans[j]))
			{
				// add the zombie
				_zombies.push_back(new Zombie);
				_zombies.back()->Init(ZOMBIE_SPEED, _humans[j]->GetPosition());
				// delete the human
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}

		// collide with player
		if (_zombies[i]->CollideWithAgent(_player))
		{
			GameEngine::FatalError("Game Over");
		}
	}


	// human collision
	for (int i = 0; i < _humans.size(); i++)
	{
		for (int j = i + 1; j < _humans.size(); j++)
		{
			_humans[i]->CollideWithAgent(_humans[j]);
		}
	}
}

void MainGame::UpdateBullets()
{
	// update and collide with world
	for (int i = 0; i < _bullets.size();)
	{
		if (_bullets[i].Update(_level->GetLevelData()))
		{
			// if true, delete
			_bullets[i] = _bullets.back();
			_bullets.pop_back();
		}
		else
		{
			i++;
		}
	}
	
	bool wasBulletRemoved;

	// collide with humans / zombies
	for (int i = 0; i < _bullets.size(); i++)
	{
		wasBulletRemoved = false;
		for (int j = 0; j < _zombies.size();)
		{
			if (_bullets[i].CollideWithAgent(_zombies[j]))
			{
				// dmg zombie
				if (_zombies[j]->ApplyDamage(_bullets[i].GetDamage()))
				{
					delete _zombies[j];
					_zombies[j] = _zombies.back();
					_zombies.pop_back();
					_numZombiesKilled++;
				}
				else
				{
					j++;
				}
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
				wasBulletRemoved = true;
				i--;
				break;
			}
			else
			{
				j++;
			}
		}

		if (!wasBulletRemoved)
		{
			for (int j = 1; j < _humans.size();)
			{
				if (_bullets[i].CollideWithAgent(_humans[j]))
				{
					// dmg zombie
					if (_humans[j]->ApplyDamage(_bullets[i].GetDamage()))
					{
						delete _humans[j];
						_humans[j] = _humans.back();
						_humans.pop_back();
						_numHumansKilled++;
					}
					else
					{
						j++;
					}
					_bullets[i] = _bullets.back();
					_bullets.pop_back();
					wasBulletRemoved = true;
					i--;
					break;
				}
				else
				{
					j++;
				}
			}
		}
	}
}

void MainGame::CheckVictory()
{
	if (_zombies.empty())
	{
		// win
		std::printf("*** You win! *** \n You killed %d humans and %d zombies. There are %d/%d civilians remaining", _numHumansKilled, _numZombiesKilled, _humans.size() - 1, _level->GetNumHumans());
		GameEngine::FatalError("");
	}
}

void MainGame::ProcessInput()
{
	SDL_Event evnt;
	const float CAMERA_SPEED = 10.0f;
	const float SCALE_SPEED = 0.1f;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				// Exit the game here!
				break;
			case SDL_MOUSEMOTION:
				_inputManager.SetMouseCoordinates(evnt.motion.x, evnt.motion.y);
				break;
			case SDL_KEYDOWN:
				_inputManager.KeyPress(evnt.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.KeyRelease(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.KeyPress(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.KeyRelease(evnt.button.button);
				break;
		}
	}

	if (_inputManager.IsKeyPressed(SDLK_w))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}

	if (_inputManager.IsKeyPressed(SDLK_s))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}

	if (_inputManager.IsKeyPressed(SDLK_d))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.IsKeyPressed(SDLK_a))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.IsKeyPressed(SDLK_q))
	{
		_camera.SetScale(_camera.GetScale() + SCALE_SPEED);
	}

	if (_inputManager.IsKeyPressed(SDLK_e))
	{
		_camera.SetScale(_camera.GetScale() - SCALE_SPEED);
	}
}

void MainGame::DrawGame()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_textureProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _textureProgram.GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	GLint pLocation = _textureProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.GetCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	_level->Draw();
	_spriteBatch.Begin();
	// draw the level
	// draw humans
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->Draw(_spriteBatch);
	}
	// draw zombies
	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->Draw(_spriteBatch);
	}
	// draw bullets
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].Draw(_spriteBatch);
	}
	_spriteBatch.End();
	_spriteBatch.RenderBatches();
	glBindTexture(GL_TEXTURE_2D, 0);
	_textureProgram.Unuse();
	// Swap our buffer and draw everything to the screen!
	_window.Swap();
}