#pragma once
#include "TextureCache.h"
#include <string>
namespace GameEngine
{
	class ResourceManager
	{
		public:
		static GLTexture GetTexture(std::string filePath);
		private:
		static TextureCache _textureCache;
	};
}