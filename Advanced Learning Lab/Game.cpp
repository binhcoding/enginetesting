#include "Game.h"
#include <iostream>
#include <string>
#include <Game Engine/Errors.h>
#include <Game Engine/GameEngine.h>
#include <Game Engine/ResourceManager.h>
#include <Game Engine/Widget.h>

//#include "ImageLoader.h"

Game::Game() : _screenWidth(1024), _screenHeight(768), _time(0), _gameState(GameState::PLAY), _maxFps(60.0f)
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
	_widgetCore.Init();
	glm::uint16 test = GameEngine::GetRandomId();

	_window.Create("Game Engine", _screenWidth, _screenHeight, 0);
	InitShaders();
	_spriteBatch.Init();
	_uiBatch.Init();
	_fpsLimiter.Init(_maxFps, 60.0f);
	//_uiCore.Init(_screenWidth, _screenHeight);
	_mainUi.Init(_screenWidth, _screenHeight, "file://C:/Users/Maishoku/Documents/Repos/enginetesting/Advanced Learning Lab/page.html");
	_mainUi.EnableMouseClick(true);
}

void Game::InitShaders()
{
	_colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.AddAttributes("vertexPosition");
	_colorProgram.AddAttributes("vertexColor");
	_colorProgram.AddAttributes("vertexUV");
	_colorProgram.LinkShaders();

	
	_uiProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_uiProgram.AddAttributes("vertexPosition");
	_uiProgram.AddAttributes("vertexColor");
	_uiProgram.AddAttributes("vertexUV");
	_uiProgram.LinkShaders();
}

void Game::Update()
{
	while (_gameState != GameState::EXIT)
	{
		// used for frame time measuring
		_fpsLimiter.Begin();
		_inputManager.Update();
		Input();
		_time += 0.01f;
		_widgetCore.Update();

		//int i = 0; // This counter makes sure we don't spiral to death!
		//// Loop while we still have steps to process.
		//while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS)
		//{
		//	// The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
		//	float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
		//	// Update all physics here and pass in deltaTime
		//	updateAgents(deltaTime);
		//	updateBullets(deltaTime);
		//	// Since we just took a step that is length deltaTime, subtract from totalDeltaTime
		//	totalDeltaTime -= deltaTime;
		//	// Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
		//	i++;
		//}

		
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

	_mainUi.Update(&sdlEvent);

	if (_inputManager.IsKeyDown(SDLK_w))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}

	if (_inputManager.IsKeyDown(SDLK_s))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}

	if (_inputManager.IsKeyDown(SDLK_d))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.IsKeyDown(SDLK_a))
	{
		_camera.SetPosition(_camera.GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}

	if (_inputManager.IsKeyDown(SDLK_q))
	{
		_camera.SetScale(_camera.GetScale() + SCALE_SPEED);
	}

	if (_inputManager.IsKeyDown(SDLK_e))
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
	_uiProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	GLint uiTextureLocation = _uiProgram.GetUniformLocation("mySampler");
	glUniform1i(uiTextureLocation, 0);
	GLint uiProjectionLocation = _uiProgram.GetUniformLocation("P");
	glm::mat4 uiCameraMatrix = _camera.GetCameraMatrixLocked();
	glUniformMatrix4fv(uiProjectionLocation, 1, GL_FALSE, &(uiCameraMatrix[0][0]));
	_uiBatch.Begin();
	_mainUi.Draw(_uiBatch);
	_uiBatch.End();
	_uiBatch.RenderBatches();
	_uiProgram.Unuse();



	_colorProgram.Use();
	glActiveTexture(GL_TEXTURE1);
	GLint colorTextureLocation = _colorProgram.GetUniformLocation("mySampler");
	glUniform1i(colorTextureLocation, 1);
	/*GLint timeLocation = _colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, _time);*/
	//_sprite.Draw();

	GLint pLocation = _colorProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix;
	_spriteBatch.Begin();
	cameraMatrix = _camera.GetCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	GameEngine::ColorRGBA8 color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	_spriteBatch.Draw(pos, uv, texture.id, 0.0f, color);
	for (int i = 0; i < _bullets.size(); i++)
	{
		//if (_camera.IsInView())
		_bullets[i].Draw(_spriteBatch);
	}
	_spriteBatch.End();
	_spriteBatch.RenderBatches();
	_colorProgram.Unuse();
	glBindTexture(GL_TEXTURE_2D, 0);
	_window.Swap();
}