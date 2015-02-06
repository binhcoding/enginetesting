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
		float startTicks = SDL_GetTicks();
		Input();
		_time += 0.01f;

		_camera.Update();
		Draw();
		CalculateFPS();
		// print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10)
		{
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks() - startTicks;
		// limit the fps to the max fps
		if (1000.0f / _maxFps > frameTicks)
		{
			SDL_Delay(1000.0f / _maxFps - frameTicks);
		}
	}
}

void Game::Input()
{
	SDL_Event sdlEvent;

	const float CAMERA_SPEED = 20.0f;
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
				break;
			case SDL_KEYDOWN:
				switch (sdlEvent.key.keysym.sym)
				{
					case SDLK_w:
						_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, CAMERA_SPEED));
						break;
					case SDLK_s:
						_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
						break;
					case SDLK_d:
						_camera.SetPosition(_camera.GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
						break;
					case SDLK_a:
						_camera.SetPosition(_camera.GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
						break;
					case SDLK_q:
						_camera.SetScale(_camera.GetScale() + SCALE_SPEED);
						break;
					case SDLK_e:
						_camera.SetScale(_camera.GetScale() - SCALE_SPEED);
						break;
				}
				break;
		}
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
	GLint timeLocation = _colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, _time);
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
	for (int i = 0; i < 1000; i++)
	{
		_spriteBatch.Draw(pos, uv, texture.id, 0.0f, color);
		_spriteBatch.Draw(pos + glm::vec4(50.0f, 0.0f, 0.0f, 0.0f), uv, texture.id, 0.0f, color);
	}
	_spriteBatch.End();
	_spriteBatch.RenderBatches();


	/*for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->Draw();
	}*/
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.Unuse();
	_window.Swap();
}

void Game::CalculateFPS()
{
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();
	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	prevTicks = currentTicks;
	// frameTimes is circular
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	int count;
	currentFrame++;
	count = (currentFrame < NUM_SAMPLES) ? currentFrame : NUM_SAMPLES;

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;
	_fps = (frameTimeAverage > 0) ? 1000.0f / frameTimeAverage : 60.0f;
}