#pragma once
#include <SDL/SDL.h>

namespace GameEngine
{
	class FpsLimiter
	{
		public:
		FpsLimiter();
		void Init(float maxFps, float desiredFps);
		void SetMaxFPS(float maxFps);
		void SetDesiredFPS(float desiredFps);
		void Begin();
		void StopDelta();
		// returns the current fps
		float End();
		float DeltaTime();
		private:
		void CalculateFPS();
		float _fps;
		float _frameTime;
		float _maxFps;
		float _desiredFps;
		float _previousTicks;
		float _deltaFrameTime;
		unsigned int _startTicks;
		const float MS_PER_SECOND = 1000;
		const float DESIRED_FRAMETIME = MS_PER_SECOND / _desiredFps;
	};

	class Time
	{
		public:
		// call this first
		static void Init()
		{
			_msPerSecond = 1000;
		}
		// call this second
		static void SetDesiredFps(float fps)
		{
			_desiredFps = fps;
			_desiredFrameTime = _msPerSecond / _desiredFps;
		}
		// access this from everywhere
		static float DeltaTime()
		{
			return _deltaFrameTime;
		}
		// set this at the beginning of the game loop
		static void Begin()
		{
			_startTicks = SDL_GetTicks();
		}
		// call this before utilizing delta time in update functions
		static void End()
		{
			float frameTime = _startTicks - _previousTicks;
			_previousTicks = _startTicks;
			_deltaFrameTime = frameTime / _desiredFrameTime;
		}
		private:
		static float _startTicks;
		static float _previousTicks;
		static float _deltaFrameTime;
		static float _msPerSecond;
		static float _desiredFrameTime;
		static float _desiredFps;
	};
}