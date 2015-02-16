#include "Widget.h"
#include <iostream>
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <SDL/sdl.h>

namespace GameEngine
{
	Widget::Widget() : _interact(false)
	{

	}


	Widget::~Widget()
	{
	}

	void Widget::Init(int width, int height, std::string filePath)
	{
		_width = width;
		_height = height;
		_webView = Awesomium::WebCore::
			instance()->CreateWebView(_width, _height, nullptr, Awesomium::kWebViewType_Offscreen);
		_webView->SetTransparent(true);
		Awesomium::WebURL url(Awesomium::WSLit(filePath.c_str()));
		_webView->LoadURL(url);
		_isInit = true;
	}

	void Widget::Draw(SpriteBatch& spriteBatch)
	{
		Awesomium::Surface* surface = _webView->surface();
		if (surface)
		{
			_surface = (WidgetSurface*)surface;
			if (_surface)
			{
				glm::vec4 pos(-512.0f, -384.0f, 1024.0f, 768.0f);
				glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
				GameEngine::ColorRGBA8 color;
				color.r = 255;
				color.g = 255;
				color.b = 255;
				color.a = 255;
				spriteBatch.Draw(pos, uv, _surface->GetTexture(), 0.0f, color);
			}
		}
	}

	void Widget::Update(SDL_Event* eventType)
	{
		if (_isInit)
		{
			if (_interact)
			{	
				switch (eventType->type)
				{
					case SDL_MOUSEMOTION:
						_webView->InjectMouseMove(eventType->motion.x, eventType->motion.y);
						break;
					case SDL_MOUSEBUTTONDOWN:
						_webView->InjectMouseDown(Awesomium::kMouseButton_Left);
						break;
					case SDL_MOUSEBUTTONUP:
						_webView->InjectMouseUp(Awesomium::kMouseButton_Left);
						break;
				}
			}
		}
	}

	void Widget::EnableMouseClick(bool val)
	{
		_interact = val;
	}

}