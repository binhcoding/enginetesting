#pragma once

namespace GameEngine
{
	class FpsLimiter
	{
		public:
		FpsLimiter();
		void Init(float maxFps);
		void SetMaxFPS(float maxFps);
		void Begin();
		// returns the current fps
		float End();
		private:
		void CalculateFPS();
		float _fps;
		float _frameTime;
		float _maxFps;
		unsigned int _startTicks;
	};
}