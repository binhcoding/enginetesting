#include "ResourceManager.h"
namespace GameEngine
{
	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::GetTexture(std::string filePath)
	{
		return _textureCache.GetTexture(filePath);
	}
}