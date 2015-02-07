#include "Window.h"
#include "Errors.h"

namespace GameEngine

{

	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;
		if (currentFlags & FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN;
		if (currentFlags & BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;

		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, flags);
		if (_sdlWindow == nullptr)
		{
			FatalError("SDL Window could not be created.");
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
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

		//normal alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::Swap()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}