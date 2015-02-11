#include "Game.h"
#include <iostream>
#include <string>
#include <Game Engine/Errors.h>
#include <Game Engine/GameEngine.h>
#include <Game Engine/ResourceManager.h>

//#include "ImageLoader.h"

Game::Game() : _screenWidth(1024), _screenHeight(760), _time(0), _gameState(GameState::PLAY), _maxFps(60.0f)
{
	_camera.Init(_screenWidth, _screenHeight);
}


Game::~Game()
{
}

void Game::Run()
{
	Init();
	/*_sprites.push_back(new GameEngine::Sprite());
	_sprites.back()->Init(0.0f, 0.0f, _screenWidth / 2, _screenHeight / 2, "Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	_sprites.push_back(new GameEngine::Sprite());
	_sprites.back()->Init(0.0f, 0.0f, _screenWidth / 2, _screenHeight / 2, "Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");*/
	//_sprite.Init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	//_playerTexture = ImageLoader::LoadPNG("Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	Update();
}

void Game::Init()
{
	GameEngine::Init();
	_window.Create("Game Engine", _screenWidth, _screenHeight, 0);
	InitShaders();
	_spriteBatch.Init();
	_fpsLimiter.Init(_maxFps);
	_uiCore.Init(_screenWidth, _screenHeight);
}

void Game::InitShaders()
{
	_colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.AddAttributes("vertexPosition");
	_colorProgram.AddAttributes("vertexColor");
	_colorProgram.AddAttributes("vertexUV");
	_colorProgram.LinkShaders();
}

void Game::Update()
{
	while (_gameState != GameState::EXIT)
	{
		// used for frame time measuring
		_fpsLimiter.Begin();
		Input();
		_time += 0.01f;

		_camera.Update();
		for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].Update())
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
			{
				i++;
			}
		}
		Draw();		
		_fps = _fpsLimiter.End();

		// print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10000)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}

void Game::Input()
{
	SDL_Event sdlEvent;

	const float CAMERA_SPEED = 10.0f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				//std::cout << sdlEvent.motion.x << " " << sdlEvent.motion.y << std::endl;
				_inputManager.SetMouseCoordinates(sdlEvent.motion.x, sdlEvent.motion.y);
				break;
			case SDL_KEYDOWN:
				_inputManager.KeyPress(sdlEvent.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.KeyRelease(sdlEvent.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.KeyPress(sdlEvent.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.KeyRelease(sdlEvent.button.button);
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

	if (_inputManager.IsKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = _inputManager.GetMouseCoordinates();
		mouseCoords = _camera.ConvertScreenToWorld(mouseCoords);
		//std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;
		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);
		_bullets.emplace_back(playerPosition, direction, 1.00f, 1000);
	}
}

void Game::Draw()
{

	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_colorProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _colorProgram.GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);
	/*GLint timeLocation = _colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, _time);*/
	//_sprite.Draw();

	GLint pLocation = _colorProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.GetCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	_spriteBatch.Begin();
	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	_uiCore.Draw(_spriteBatch);
	_spriteBatch.Draw(pos, uv, texture.id, 0.0f, color);
	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].Draw(_spriteBatch);
	}
	_spriteBatch.End();
	_spriteBatch.RenderBatches();
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.Unuse();
	_window.Swap();
}