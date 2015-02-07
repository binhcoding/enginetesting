#include "InputManager.h"

namespace GameEngine
{

	InputManager::InputManager() : _mouseCoordinates(0, 0)
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::KeyPress(unsigned int keyId)
	{
		_keyMap[keyId] = true;
	}

	void InputManager::KeyRelease(unsigned int keyId)
	{
		_keyMap[keyId] = false;
	}

	void InputManager::SetMouseCoordinates(float x, float y)
	{
		_mouseCoordinates.x = x;
		_mouseCoordinates.y = y;
	}

	bool InputManager::IsKeyPressed(unsigned int keyId)
	{
		auto iterator = _keyMap.find(keyId);
		if (iterator != _keyMap.end())
		{
			return iterator->second;
		}
		return false;
	}

	
}