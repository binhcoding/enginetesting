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
		void KeyPress(unsigned int keyId);
		void KeyRelease(unsigned int keyId);
		bool IsKeyPressed(unsigned int keyId);
		void SetMouseCoordinates(float x, float y);
		glm::vec2 GetMouseCoordinates() const { return _mouseCoordinates; }
		private:
		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoordinates;
	};

}