#include "pch.h"
#include "SellBuilding.h"
#include "SceneGame.h"

SellBuilding::SellBuilding(const std::string& name) : Building(name)
{
}

void SellBuilding::Sell(SCUnit::Type t, SCUnit::Rarity r)
{
	sceneGame->SellUnit(t, r);
}

void SellBuilding::Init()
{
	Building::Init();
	textureId = "graphics/sell.png";
	SetTexture();
}

void SellBuilding::Reset()
{
	Building::Reset();
}

void SellBuilding::Update(float dt)
{
	Building::Update(dt);
}

void SellBuilding::LateUpdate(float dt)
{
	Building::LateUpdate(dt);
}
