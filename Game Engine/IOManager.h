#pragma once
#include <vector>
namespace GameEngine
{
	class IOManager
	{
		public:
		static bool ReadFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};

}