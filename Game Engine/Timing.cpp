#include "Timing.h"
#include <SDL/SDL.h>

namespace GameEngine
{
	FpsLimiter::FpsLimiter()
	{

	}

	void FpsLimiter::Init(float maxFps)
	{
		SetMaxFPS(maxFps);

	}

	
	void FpsLimiter::SetMaxFPS(float maxFps)
	{
		_maxFps = maxFps;
	}

	void FpsLimiter::Begin()
	{
		_startTicks = SDL_GetTicks();
	}

	// returns the current fps
	float FpsLimiter::End()
	{
		CalculateFPS();
		float frameTicks = SDL_GetTicks() - _startTicks;
		// limit the fps to the max fps
		if (1000.0f / _maxFps > frameTicks)
		{
			SDL_Delay((Uint32)1000.0f / _maxFps - frameTicks);
		}
		return _fps;
	}

	void FpsLimiter::CalculateFPS()
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
}