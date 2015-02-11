#pragma once
#include <Awesomium/Surface.h>
#include <Game Engine/GLTexture.h>

class UiSurface : public Awesomium::Surface
{
	public:
	UiSurface();
	void Paint(unsigned char* src_buffer, int src_row_span, const Awesomium::Rect& src_rect, const Awesomium::Rect &dest_rect);
	void Scroll(int dx, int dy, const Awesomium::Rect &clip_rect);
	GLuint GetTexture();
	private:
	GameEngine::GLTexture* _uiTexture;
};

