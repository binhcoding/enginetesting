#include "UiSurface.h"

UiSurface::UiSurface(int width, int height) : _uiTexture(0), _width(width), _height(height), _data(0)
{
	_data = new unsigned char[_width * _height * 4];
	_updateTexture = false;
	glGenTextures(1, &_uiTexture);
	glBindTexture(GL_TEXTURE_2D, _uiTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	GLfloat largest_supported_anisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropy);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void UiSurface::Paint(unsigned char* src_buffer, int src_row_span, const Awesomium::Rect& src_rect, const Awesomium::Rect &dest_rect)
{
	for (int row = 0; row < dest_rect.height; row++)
		memcpy(_data + (row + dest_rect.y) * _width * 4 + (dest_rect.x * 4),
		src_buffer + (row + src_rect.y) * src_row_span + (src_rect.x * 4),
		dest_rect.width * 4);
	_updateTexture = true;
}

void UiSurface::Scroll(int dx, int dy, const Awesomium::Rect &clip_rect)
{

}

GLuint UiSurface::GetTexture()
{
	UpdateTexture();
	return _uiTexture;
}

void UiSurface::UpdateTexture()
{
	if (_updateTexture)
	{
		glBindTexture(GL_TEXTURE_2D, _uiTexture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_BGRA, GL_UNSIGNED_BYTE, _data);
		_updateTexture = false;
	}
}