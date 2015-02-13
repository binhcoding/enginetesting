#pragma once
#include <glm/glm.hpp>
#include <Game Engine/GLTexture.h>
#include <Game Engine/Vertex.h>

struct Tile
{
	bool collidable;
	glm::vec4 positionAndSize;
	GameEngine::GLTexture texture;
	GameEngine::ColorRGBA8 color;
};