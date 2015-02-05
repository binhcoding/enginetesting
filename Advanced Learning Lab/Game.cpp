#include "Game.h"
#include <iostream>
#include <string>
#include "Errors.h"
//#include "ImageLoader.h"

Game::Game() : _screenWidth(1024), _screenHeight(760), _time(0), p_window(nullptr), _gameState(GameState::PLAY), _maxFps(60.0f)
{

}


Game::~Game()
{
}

void Game::Run()
{
	Init();
	_sprites.push_back(new Sprite());
	_sprites.back()->Init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	_sprites.push_back(new Sprite());
	_sprites.back()->Init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	//_sprite.Init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	//_playerTexture = ImageLoader::LoadPNG("Textures/JimmyJumpPack/PNG/CharacterRight_Standing.png");
	Update();
}

void Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	p_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (p_window == nullptr)
	{
		FatalError("SDL Window could not be created.");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(p_window);
	if (glContext == nullptr)
	{
		FatalError("SDL_GL context could not be created.");
	}

	GLenum glError = glewInit();
	if (glError != GLEW_OK)
	{
		FatalError("Glew failed to initialize.");
	}

	printf("*** OpenGL Version: %s ***", glGetString(GL_VERSION));
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// vsync
	SDL_GL_SetSwapInterval(1);

	InitShaders();
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
	for (int i = 0; i < _sprites.size(); i++)
	{
		_sprites[i]->Draw();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	_colorProgram.Unuse();
	SDL_GL_SwapWindow(p_window);
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