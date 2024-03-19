#include "pch.h"
#include "UIAnimatorEditer.h"
#include "SpriteGo.h"

UIAnimatorEditer::UIAnimatorEditer(const std::string& name)
{

}

UIAnimatorEditer::~UIAnimatorEditer()
{

}

void UIAnimatorEditer::Init()
{
	NewSpriteGo("MainBG", "graphics/UI/Bg.png");
	sprites["MainBG"]->SetOrigin(Origins::MC);
	sprites["MainBG"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , FRAMEWORK.GetWindowSize().y * 0.5f, });
	sprites["MainBG"]->SetScale({ 1.0f , 1.0f });
	sprites["MainBG"]->sortLayer = 1;

	NewSpriteGo("TextuerLoad", "graphics/UI/button.png");
	sprites["TextuerLoad"]->SetOrigin(Origins::TL);
	sprites["TextuerLoad"]->SetPosition({ 0, FRAMEWORK.GetWindowSize().y * 0.5f, });
	sprites["TextuerLoad"]->sortLayer = 1;

	UiInit();
	ObjectsSort();
}

void UIAnimatorEditer::Release()
{
	GameObject::Release();

	UiDelete();
}

void UIAnimatorEditer::Reset()
{
	GameObject::Reset();
}

void UIAnimatorEditer::Update(float dt)
{
	GameObject::Update(dt);
}

void UIAnimatorEditer::LateUpdate(float dt)
{
	GameObject::LateUpdate(dt);
}
