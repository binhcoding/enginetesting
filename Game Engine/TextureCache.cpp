#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace GameEngine
{

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::GetTexture(std::string& filePath)
	{
		// look up the texture and see if its in the map
		std::map<std::string, GLTexture>::iterator mapIterator = _textureMap.find(filePath);

		// check if its not in the map
		if (mapIterator == _textureMap.end())
		{
			// load texture
			GLTexture newTexture = ImageLoader::LoadPNG(filePath);
			// insert into the map
			/*std::pair<std::string, GLTexture> newPair(filePath, newTexture);
			_textureMap.insert(newPair);*/
			_textureMap.insert(make_pair(filePath, newTexture));
			//std::cout << "Adding to cache." << std::endl;
			return newTexture;
		}
		//std::cout << "Pulled from cache." << std::endl;
		return mapIterator->second;
	}
}