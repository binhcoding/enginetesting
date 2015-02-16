#pragma once
#include "Entity.h"
#include <string>
#include "WidgetSurface.h"
#include "SpriteBatch.h"
#include <sdl/SDL.h>

namespace GameEngine
{
	class Widget : public Entity
	{
		public:
		Widget();
		virtual ~Widget();
		// when you declare a widget
		// you need to specify the source file
		void Init(int width, int height, std::string filePath);
		void Draw(SpriteBatch& spriteBatch);
		void Update(SDL_Event* eventType);
		void EnableMouseClick(bool val);
		private:
		int _width, _height;
		Awesomium::WebView* _webView;
		WidgetSurface* _surface;
		bool _interact;
	};

}