#include "pch.h"
#include "SellBuilding.h"

SellBuilding::SellBuilding(const std::string& name) : Building(name)
{
}

void SellBuilding::Init()
{
	Building::Init();
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
