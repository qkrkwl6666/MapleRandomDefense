#include "pch.h"
#include "Crosshair.h"

Crosshair::Crosshair(const std::string& name)
{
	sortLayer = 20;
	textureId = "graphics/UI/cursor.png";
	SetTexture(textureId);
	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::TL);
}

void Crosshair::Init()
{
	SpriteGo::Init();
}

void Crosshair::Release()
{
	SpriteGo::Release();
}

void Crosshair::Reset()
{
	SpriteGo::Reset();
}

void Crosshair::Update(float dt)
{
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToUi((sf::Vector2i)InputMgr::GetMousePos());
	SetPosition(mouseWorldPos);
}

void Crosshair::Draw(sf::RenderWindow & window)
{
	SpriteGo::Draw(window);
}
