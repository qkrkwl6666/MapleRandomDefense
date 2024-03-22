#include "pch.h"
#include "UpgradeBuilding.h"
#include "SceneGame.h"
UpgradeBuilding::UpgradeBuilding(const std::string& name, Building::Races r) : Building(name) , races(r)
{
}

void UpgradeBuilding::Upgrade()
{
	switch (races)
	{
	case Building::Races::Zerg:
		if (sceneGame->GetMineral() < (10 + 2 * sceneGame->GetHydraliskUpgrade()))
		{
			sceneGame->message(SceneGame::MessageType::NotEnoughMinerals);
			return;
		}
		sceneGame->SetMineral(sceneGame->GetMineral() - (10 + 2 * sceneGame->GetHydraliskUpgrade()));
		sceneGame->SetHydraliskUpgrade(sceneGame->GetHydraliskUpgrade() + 1);
		break;
	case Building::Races::Protoss:
		if (sceneGame->GetMineral() < (12 + 3 * sceneGame->GetDragoonUpgrade()))
		{
			sceneGame->message(SceneGame::MessageType::NotEnoughMinerals);
			return;
		}
		sceneGame->SetMineral(sceneGame->GetMineral() - (12 + 3 * sceneGame->GetDragoonUpgrade()));
		sceneGame->SetDragoonUpgrade(sceneGame->GetDragoonUpgrade() + 1);
		break;
	case Building::Races::Terran:
		if (sceneGame->GetMineral() < (12 + 3 * sceneGame->GetGhostUpgrade()))
		{
			sceneGame->message(SceneGame::MessageType::NotEnoughMinerals);
			return;
		}
		sceneGame->SetMineral(sceneGame->GetMineral() - (12 + 3 * sceneGame->GetGhostUpgrade()));
		sceneGame->SetGhostUpgrade(sceneGame->GetGhostUpgrade() + 1);
		break;
	default:
		break;
	}
	sceneGame->UpgradeUpdate();
}

void UpgradeBuilding::Init()
{
	Building::Init();
	switch (races)
	{
	case Building::Races::Zerg:
		textureId = "graphics/zerg.png";
		break;
	case Building::Races::Protoss:
		textureId = "graphics/protoss.png";
		break;
	case Building::Races::Terran:
		textureId = "graphics/terran.png";
		break;
	default:
		break;
	}
	SetTexture();
}

void UpgradeBuilding::Reset()
{
	Building::Reset();
}

void UpgradeBuilding::Update(float dt)
{
	Building::Update(dt);
}

void UpgradeBuilding::LateUpdate(float dt)
{
	Building::LateUpdate(dt);
}
