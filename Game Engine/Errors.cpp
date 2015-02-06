#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

namespace GameEngine
{
	void FatalError(std::string errorString)
	{
		// TODO: error handling class
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit...";
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(1);
	}
}