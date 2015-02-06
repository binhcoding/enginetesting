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
		void CalculateFPS();

		GameEngine::Window _window;
		int _screenWidth;
		int _screenHeight;
		GameState _gameState;

		GameEngine::Sprite _sprite;
		//std::vector<GameEngine::Sprite*> _sprites;
		GameEngine::GLSLProgram _colorProgram;
		GameEngine::SpriteBatch _spriteBatch;
		float _time;
		float _fps;
		float _frameTime;
		float _maxFps;
		GameEngine::Camera2D _camera;
};

