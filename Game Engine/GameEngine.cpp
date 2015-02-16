#include <SDL/SDL.h>
#include <GL/glew.h>
#include "GameEngine.h"
#include <random>
#include <ctime>

namespace GameEngine
{
	int Init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 0;
	}

	glm::uint16 GetRandomId()
	{
		static std::mt19937 randomEngine(time(nullptr));
		static std::uniform_int_distribution<int> randomId(0, 65536);
		
		return (glm::uint16)randomId(randomEngine);
	}
}