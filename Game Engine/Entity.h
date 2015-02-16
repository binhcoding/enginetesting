#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <GLM/glm.hpp>
#include "Vertex.h"
#include <string>


namespace GameEngine
{
	class Entity
	{
		public:
		Entity();
		virtual ~Entity();


		//virtual void Init();
		//virtual void Draw();
		//virtual void Update();

		std::string GetTag();
		glm::uint16 GetId();

		protected:
		GLTexture _texture;
		glm::vec2 _position;
		ColorRGBA8 _color;
		glm::uint16 _id;
		std::string _tag;
		bool _isInit;
	};
}