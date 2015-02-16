#pragma once
#include <Awesomium/Surface.h>
#include <GL/glew.h>

namespace GameEngine
{
	class WidgetSurface : public Awesomium::Surface
	{
		public:
		WidgetSurface(int width, int height);
		~WidgetSurface();
		void Paint(unsigned char* src_buffer, int src_row_span, const Awesomium::Rect& src_rect, const Awesomium::Rect &dest_rect);
		void Scroll(int dx, int dy, const Awesomium::Rect &clip_rect);
		GLuint GetTexture();
		private:
		void UpdateTexture();

		GLuint _uiTexture;
		int _width, _height;
		bool _updateTexture;
		unsigned char* _data;

	};
}