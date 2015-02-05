#include "IOManager.h"
#include <fstream>

bool IOManager::ReadFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	// seek to end
	file.seekg(0, std::ios::end);

	// get the file size in bytes
	int fileSize = file.tellg();

	file.seekg(0, std::ios::beg);

	// reduce the file size by any header bytes that might be present
	fileSize -= file.tellg();
	buffer.resize(fileSize);

	file.read((char *)&(buffer[0]), fileSize);
	file.close();
	return true;
}
