#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::GetTexture(std::string& filePath)
{
	return _textureCache.GetTexture(filePath);
}