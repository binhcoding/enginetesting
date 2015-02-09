#pragma once

#include <Game Engine/Window.h>
#include <Game Engine/GLSLProgram.h>
#include <Game Engine/Camera2D.h>
#include <Game Engine/InputManager.h>
#include <Game Engine/SpriteBatch.h>
#include <Game Engine/Timing.h>
#include "Level.h"
#include <vector>
#include "Player.h"
#include "Bullet.h"

class Zombie;

class MainGame
{
public:
    MainGame();
    ~MainGame();

    /// Runs the game
    void Run();

private:
    /// Initializes the core systems
    void InitSystems();

    /// Initializes the shaders
    void InitShaders();

    /// Main game loop for the program
    void GameLoop();

    /// Handles input processing
    void ProcessInput();

    /// Renders the game
    void DrawGame();

	// update all the agents
	void UpdateAgents();

	//update all the bullets
	void UpdateBullets();

	// check victory conditions
	void CheckVictory();

    /// Member Variables
	GameEngine::Window _window; ///< The game window
    
	GameEngine::GLSLProgram _textureProgram; ///< The shader program

	GameEngine::InputManager _inputManager; ///< Handles input

	GameEngine::Camera2D _camera; ///< Main Camera

	GameEngine::SpriteBatch _spriteBatch;

	GameEngine::FpsLimiter _fpsLimiter;

	std::vector<Human*> _humans; // vector of all humans

	std::vector<Zombie*> _zombies;

	std::vector<Bullet> _bullets;

	int _numHumansKilled; // humans killed by player
	int _numZombiesKilled; // zombies killed by player
	
	
	Player* _player;

	Level* _level;
	int _screenWidth;
	int _screenHeight;
	float _maxFps;
	float _fps;
};

