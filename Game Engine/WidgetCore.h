#pragma once
#include <Awesomium/WebCore.h>
#include <memory>
#include "WidgetSurfaceFactory.h"

namespace GameEngine
{
	class WidgetCore
	{
		public:
		WidgetCore();
		~WidgetCore();

		void Init();
		void Update();

		private:
		Awesomium::WebCore* _webCore;
		std::unique_ptr<WidgetSurfaceFactory> _surfaceFactory;
	};

}