#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace GameEngine
{
	class InputManager
	{
		public:
		InputManager();
		~InputManager();
		void Update();
		void KeyPress(unsigned int keyId);
		void KeyRelease(unsigned int keyId);
		// returns true if the key is held down
		bool IsKeyDown(unsigned int keyId);
		// returns true if the key was just pressed;
		bool IsKeyPressed(unsigned int keyId);

		void SetMouseCoordinates(float x, float y);
		glm::vec2 GetMouseCoordinates() const { return _mouseCoordinates; }
		private:
		bool WasKeyDown(unsigned int keyId);

		std::unordered_map<unsigned int, bool> _keyMap;
		std::unordered_map<unsigned int, bool> _previousKeyMap;
		glm::vec2 _mouseCoordinates;
	};

}