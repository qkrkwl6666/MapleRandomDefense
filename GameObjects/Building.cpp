#include "pch.h"
#include "Building.h"
#include "SceneGame.h"


Building::Building(const std::string& name) : SpriteGo(name)
{
}

void Building::Init()
{
	SpriteGo::Init();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));


	isSelectSprite = std::make_shared<SpriteGo>();
	isSelectSprite->SetTexture("graphics/UI/cursorsSelect.png");
	isSelectSprite->SetScale({ 4.f , 4.f });
	isSelectSprite->SetOrigin(Origins::MC);
	isSelectSprite->SetActive(false);
}

void Building::Reset()
{
	SpriteGo::Reset();
}

void Building::Draw(sf::RenderWindow& window)
{
	if (isSelectSprite->GetActive() && isSelect == true)
	{
		isSelectSprite->Draw(window);
	}
	SpriteGo::Draw(window);
}

void Building::Update(float dt)
{
	SpriteGo::Update(dt);

	if (isSelectSprite->GetActive() && isSelect)
	{
		isSelectSprite->SetPosition({ GetPosition().x + 50.f , GetPosition().y + 50.f});
	}
}

void Building::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}

void Building::SetSelect(bool isSelect)
{
	this->isSelect = isSelect;
	isSelectSprite->SetActive(isSelect);
}
