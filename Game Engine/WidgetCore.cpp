#include "WidgetCore.h"

namespace GameEngine
{

	WidgetCore::WidgetCore()
	{
	}


	WidgetCore::~WidgetCore()
	{
	}

	void WidgetCore::Init()
	{
		_webCore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
		_surfaceFactory = std::make_unique<WidgetSurfaceFactory>();
		Awesomium::WebCore::instance()->set_surface_factory(_surfaceFactory.get());
	}


	void WidgetCore::Update()
	{
		_webCore->Update();
	}
}