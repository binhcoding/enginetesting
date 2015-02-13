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

	bool InputManager::IsKeyDown(unsigned int keyId)
	{
		auto iterator = _keyMap.find(keyId);
		if (iterator != _keyMap.end())
		{
			return iterator->second;
		}
		return false;
	}

	bool InputManager::IsKeyPressed(unsigned int keyId)
	{
		if (IsKeyDown(keyId) && !WasKeyDown(keyId))
			return true;
		return false;
	}

	void InputManager::Update()
	{
		// loop through _keyMap using a for each loop and copy it over to _previousKeyMap
		for (auto& iterator : _keyMap)
		{
			_previousKeyMap[iterator.first] = iterator.second;
		}
	}

	bool InputManager::WasKeyDown(unsigned int keyId)
	{
		auto iterator = _previousKeyMap.find(keyId);
		if (iterator != _previousKeyMap.end())
		{
			return iterator->second;
		}
		return false;
	}

	
}