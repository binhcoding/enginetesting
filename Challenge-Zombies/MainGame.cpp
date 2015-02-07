#include "MainGame.h"

#include <Game Engine/GameEngine.h>
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <iostream>

MainGame::MainGame() : _screenWidth(1080), _screenHeight(720), _maxFps(60.0f)
{
	// Empty
	_camera.Init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
	// IMPLEMENT THIS!
}

void MainGame::run()
{
	// IMPLEMENT THIS!
	initSystems();
	gameLoop();
}

void MainGame::initSystems()
{
	GameEngine::Init();
	_window.Create("Zambies", _screenWidth, _screenHeight, 0);
	// IMPLEMENT THIS!
	_level.LoadLevel("Levels/level1.txt");
	initShaders();
	_spriteBatch.Init();
	_fpsLimiter.Init(_maxFps);
}

void MainGame::initShaders()
{
	// Compile our color shader
	_textureProgram.CompileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	_textureProgram.AddAttributes("vertexPosition");
	_textureProgram.AddAttributes("vertexColor");
	_textureProgram.AddAttributes("vertexUV");
	_textureProgram.LinkShaders();
}

void MainGame::gameLoop()
{
	// IMPLEMENT THIS!
	while (true)
	{
		_fpsLimiter.Begin();
		processInput();
		_camera.Update();
		drawGame();
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

void MainGame::processInput()
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

void MainGame::drawGame()
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
	_spriteBatch.Begin();
	_level.Draw(_spriteBatch);
	_spriteBatch.End();
	_spriteBatch.RenderBatches();
	glBindTexture(GL_TEXTURE_2D, 0);
	_textureProgram.Unuse();
	// Swap our buffer and draw everything to the screen!
	_window.Swap();
}