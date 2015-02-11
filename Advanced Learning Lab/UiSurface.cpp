#include "UiSurface.h"

UiSurface::UiSurface() : _uiTexture(nullptr)
{

}

void UiSurface::Paint(unsigned char* src_buffer, int src_row_span, const Awesomium::Rect& src_rect, const Awesomium::Rect &dest_rect)
{
	if (_uiTexture == nullptr)
	{
		_uiTexture = new GameEngine::GLTexture;
		_uiTexture->id = 0;
		glGenTextures(1, &(_uiTexture->id));
	}	

	glBindTexture(GL_TEXTURE_2D, _uiTexture->id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, src_rect.width, src_rect.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(src_buffer[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	_uiTexture->width = src_rect.width;
	_uiTexture->height = src_rect.height;
}

void UiSurface::Scroll(int dx, int dy, const Awesomium::Rect &clip_rect)
{

}

GLuint UiSurface::GetTexture()
{
	return _uiTexture->id;
}