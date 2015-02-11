#include "UiCore.h"


UiCore::UiCore() : _mainUiSurface(nullptr), _webCore(nullptr), _mainUi(nullptr)
{

}


UiCore::~UiCore()
{
	_mainUi->Destroy();
	Awesomium::WebCore::Shutdown();
}

void UiCore::Init(int width, int height)
{
	_webCore = Awesomium::WebCore::Initialize(Awesomium::WebConfig());
	_uiSurfaceFactory = std::make_unique<UiSurfaceFactory>();
	_webCore->set_surface_factory(_uiSurfaceFactory.get());
	_mainUi = _webCore->CreateWebView(1024, 768, nullptr, Awesomium::kWebViewType_Offscreen);
	_mainUi->SetTransparent(true);
	LoadMainUi("http://www.reddit.com");
}

void UiCore::LoadMainUi(std::string path)
{
	Awesomium::WebURL url(Awesomium::WSLit(path.c_str()));
	_mainUi->LoadURL(url);
	while (_mainUi->IsLoading())
		_webCore->Update();
	//Sleep(300);
	_webCore->Update();
	_mainUiSurface = (UiSurface*)_mainUi->surface();
	
}

void UiCore::Draw(GameEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 pos(0.0f, 0.0f, 1024.0f, 768.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	spriteBatch.Draw(pos, uv, _mainUiSurface->GetTexture(), 0.0f, color);
}