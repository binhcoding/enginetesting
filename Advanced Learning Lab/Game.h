#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include <vector>

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

		SDL_Window* p_window = nullptr;
		int _screenWidth;
		int _screenHeight;
		GameState _gameState;

		Sprite _sprite;
		std::vector<Sprite*> _sprites;
		GLSLProgram _colorProgram;
		float _time;
		float _fps;
		float _frameTime;
		float _maxFps;
};

