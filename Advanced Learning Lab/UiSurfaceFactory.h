#pragma once
#include <Awesomium/Surface.h>
#include "UiSurface.h"

class UiSurfaceFactory : public Awesomium::SurfaceFactory
{
	public:
	virtual Awesomium::Surface* CreateSurface(Awesomium::WebView * view, int width, int height)
	{
		return new UiSurface();
	}

	virtual void DestroySurface(Awesomium::Surface * surface)
	{
		delete surface;
	}
};

