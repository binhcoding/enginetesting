#pragma once
#include <map>
#include <string>
#include "GLTexture.h"
namespace GameEngine
{
	class TextureCache
	{
		public:
		TextureCache();
		~TextureCache();
		GLTexture GetTexture(std::string& filePath);
		private:
		std::map<std::string, GLTexture> _textureMap;
	};
}