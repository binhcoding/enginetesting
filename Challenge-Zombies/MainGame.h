#pragma once

#include <Game Engine/Window.h>
#include <Game Engine/GLSLProgram.h>
#include <Game Engine/Camera2D.h>
#include <Game Engine/InputManager.h>
#include <Game Engine/SpriteBatch.h>
#include <Game Engine/Timing.h>
#include "Level.h"

class MainGame
{
public:
    MainGame();
    ~MainGame();

    /// Runs the game
    void run();

private:
    /// Initializes the core systems
    void initSystems();

    /// Initializes the shaders
    void initShaders();

    /// Main game loop for the program
    void gameLoop();

    /// Handles input processing
    void processInput();

    /// Renders the game
    void drawGame();

    /// Member Variables
	GameEngine::Window _window; ///< The game window
    
	GameEngine::GLSLProgram _textureProgram; ///< The shader program

	GameEngine::InputManager _inputManager; ///< Handles input

	GameEngine::Camera2D _camera; ///< Main Camera

	GameEngine::SpriteBatch _spriteBatch;

	GameEngine::FpsLimiter _fpsLimiter;

	Level _level;
	int _screenWidth;
	int _screenHeight;
	float _maxFps;
	float _fps;
};

