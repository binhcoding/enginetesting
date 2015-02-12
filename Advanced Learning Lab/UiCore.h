#pragma once
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/Surface.h>
#include "UiSurface.h"
#include <Game Engine/SpriteBatch.h>
#include "UiSurfaceFactory.h"
#include <memory>

class UiCore
{
	public:
	UiCore();
	~UiCore();
	void Init(int width, int height);
	void LoadMainUi(std::string path);
	void Update();
	void Draw(GameEngine::SpriteBatch& spriteBatch);
	private:
	Awesomium::WebCore* _webCore;
	Awesomium::WebView* _mainUi;
	UiSurface* _mainUiSurface;
	std::unique_ptr<UiSurfaceFactory> _uiSurfaceFactory;
};

