#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Game Engine/Sprite.h>
#include <Game Engine/GLSLProgram.h>
#include <Game Engine/GLTexture.h>
#include <Game Engine/Window.h>
#include <vector>
#include <Game Engine/Camera2D.h>
#include <Game Engine/SpriteBatch.h>
#include <Game Engine/InputManager.h>
#include <Game Engine/Timing.h>
#include "Bullet.h"
#include "UiCore.h"
enum class GameState { PLAY, EXIT };


class Game
{
	public:
		Game();
		~Game();
		void Run();
	private:
		void Init();
		void InitShaders();
		void Update();
		void Input();
		void Draw();

		GameEngine::Window _window;
		int _screenWidth;
		int _screenHeight;
		GameState _gameState;

		GameEngine::Sprite _sprite;
		//std::vector<GameEngine::Sprite*> _sprites;
		GameEngine::GLSLProgram _colorProgram;
		GameEngine::SpriteBatch _spriteBatch;

		std::vector<Bullet> _bullets;

		float _time;
		float _maxFps;
		float _fps;

		UiCore _uiCore;
		GameEngine::Camera2D _camera;
		GameEngine::InputManager _inputManager;
		GameEngine::FpsLimiter _fpsLimiter;
		GameEngine::GLTexture _gameUi;
};

