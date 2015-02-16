#include "Camera2D.h"

namespace GameEngine
{
	Camera2D::Camera2D() : _position(0.0f, 0.0f), _cameraMatrix(1.0f), _scale(1.0f),
		_needsMatrixUpdate(true), _screenWidth(500), _screenHeight(500)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::Init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)screenHeight);
	}


	void Camera2D::Update()
	{
		if (_needsMatrixUpdate)
		{
			// camera translation
			glm::vec3 translate(-_position.x + _screenWidth / 2,
				-_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			//camera scale
			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
			_needsMatrixUpdate = false;

		}
	}

	glm::vec2 Camera2D::ConvertScreenToWorld(glm::vec2 screenCoords)
	{
		// invert y direction
		screenCoords.y = _screenHeight - screenCoords.y;

		// convert from 0,0 top left and sh/sw bottom right to
		// forces 0,0 to the center
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		// scale the coordinates
		screenCoords /= _scale;
		// translate with the camera position
		screenCoords += _position;
		return screenCoords;
	}

	glm::mat4 Camera2D::GetCameraMatrixLocked()
	{
		glm::vec3 translate(_screenWidth / 2, _screenHeight / 2, 0.0f);
		return glm::translate(_orthoMatrix, translate);
	}

	bool Camera2D::IsInView(const glm::vec2& position, const glm::vec2& dimensions)
	{
		glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / _scale;

		//axis aligned bounding box
		// min distance before collision
		const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2;
		const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2;

		glm::vec2 centerPos = position;
		glm::vec2 centerCameraPos = _position;
		glm::vec2 distVec = centerPos - centerCameraPos;

		// depth of collision
		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		if (xDepth > 0 && yDepth > 0)
		{
			  //collision
			return true;
		}
		return false;
	}

}