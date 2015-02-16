#pragma once
#include <Awesomium/Surface.h>
#include "WidgetSurface.h"

namespace GameEngine
{

	class WidgetSurfaceFactory : public Awesomium::SurfaceFactory
	{
		public:
		virtual Awesomium::Surface* CreateSurface(Awesomium::WebView * view, int width, int height)
		{
			return new WidgetSurface(width, height);
		}

		virtual void DestroySurface(Awesomium::Surface * surface)
		{
			delete surface;
		}
	};

}