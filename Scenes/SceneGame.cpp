#include "pch.h"
#include "Scene.h"
#include "SceneGame.h"
#include "TileSet.h"
#include "ShapeGo.h"
#include <Windows.h>
#include "Crosshair.h"
#include "Interface.h"
#include "UpgradeBuilding.h"
#include "SellBuilding.h"
#include "SCUnit.h"
#include "Hydralisk.h"
#include "Dragoon.h"
#include "Ghost.h"
#include "Enemy.h"
#include "Zergling.h"
#include "Spawner.h"
#include "Civilian.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{

}

void SceneGame::SellUnit(SCUnit::Type t, SCUnit::Rarity r)
{
	switch (t)
	{
	case SCUnit::Type::Hydralisk:
		for (auto it = HydraliskList.begin(); it != HydraliskList.end();)
		{
			SCUnit* hydralisk = *it;
			if (hydralisk && hydralisk->GetRarity() == r)
			{
				it = HydraliskList.erase(it);
				for (auto* data : AllUnitList)
				{
					if (data == hydralisk)
					{
						AllUnitList.remove(data);
						break;
					}
				}
				hydralisk->SellThis();
				return;
			}
			else
			{
				it++;
			}
		}

		break;
	case SCUnit::Type::Dragoon:
		for (auto it = DragoonList.begin(); it != DragoonList.end();)
		{
			SCUnit* dragoon = *it;
			if (dragoon && dragoon->GetRarity() == r)
			{
				it = DragoonList.erase(it);
				
				dragoon->SellThis();
				return;
			}

			else
			{
				it++;
			}
		}
		break;
	case SCUnit::Type::Ghost:
		for (auto it = GhostList.begin(); it != GhostList.end();)
		{
			SCUnit* ghost = *it;
			if (ghost && ghost->GetRarity() == r)
			{
				it = GhostList.erase(it);
				ghost->SellThis();
				return;
			}
			else
			{
				it++;
			}
		}
		break;
	default:
		break;
	}
	std::cout << "유닛 없음" << std::endl;
}

Enemy* SceneGame::FindEnemy(sf::Vector2f pos, float range)
{
	float distance;
	for (auto go : EnemyList)
	{
		distance = Utils::Distance(pos, go->GetPosition());
		if (distance < range * 32)
		{
			return go;
		}
	}
	return nullptr;
}

void SceneGame::message(MessageType m)
{
	switch (m)
	{
	case SceneGame::MessageType::NONE:
		break;
	case SceneGame::MessageType::NotEnoughMinerals:
		std::cout << "미네랄 부족" << std::endl;
		break;
	case SceneGame::MessageType::count:
		break;
	default:
		break;
	}
}

void SceneGame::message(MessageType m, SCUnit::Type t, SCUnit::Rarity r)
{

	std::string type;
	switch (t)
	{
	case SCUnit::Type::Hydralisk:
		type = "히드라 ";
		break;
	case SCUnit::Type::Dragoon:
		type = "드라군 ";
		break;
	case SCUnit::Type::Ghost:
		type = "고스트 ";
		break;
	default:
		break;
	}

	std::string rarity;
	switch (r)
	{
	case SCUnit::Rarity::Common:
		rarity = "일반]";
		break;
	case SCUnit::Rarity::Rare:
		rarity = "레어]";
		break;
	case SCUnit::Rarity::Ancient:
		rarity = "고대]";
		break;
	case SCUnit::Rarity::Artifact:
		rarity = "유물]";
		break;
	case SCUnit::Rarity::Saga:
		rarity = "서사]";
		break;
	case SCUnit::Rarity::Legendary:
		rarity = "전설] **************";
		break;
	case SCUnit::Rarity::Mythic:
		rarity = "신화] *********************";
		break;
	case SCUnit::Rarity::Primeval:
		rarity = "태초] ***************************** ";
		break;
	}

	switch (m)
	{
	case SceneGame::MessageType::BuyUnit:
		std::cout << "[" << type << rarity << std::endl;
		break;
	case SceneGame::MessageType::SellUnit:
		std::cout << "[유닛을 판매했습니다 : " << type << rarity << std::endl;
		break;
	default:
		break;
	}
}


void SceneGame::message(int i)
{
	std::cout << "+ " << i << "원" << std::endl;
}

void SceneGame::UpgradeUpdate()
{
	for (auto go : HydraliskList)
	{
		SCUnit* hydralisk = go;
		hydralisk->SetUpgrade(hydraliskUpgrade);
	}

	for (auto go : GhostList)
	{
		SCUnit* ghost = go;
		ghost->SetUpgrade(ghostUpgrade);
	}

	for (auto go : DragoonList)
	{
		SCUnit* dragoon = go;
		dragoon->SetUpgrade(dragoonUpgrade);
	}
}

void SceneGame::Init()
{
	tileSet = new TileSet();
	AddGo(tileSet, Scene::World);

	mouse = FRAMEWORK.GetMouse();

	leftFiller = new ShapeGo<sf::RectangleShape>("leftFiller");
	rightFiller = new ShapeGo<sf::RectangleShape>("rightFiller");


	leftFiller->SetSize({ 
		((float)FRAMEWORK.GetWindowSize().x / 8),
		(float) FRAMEWORK.GetWindowSize().y });

	rightFiller->SetSize({ 
		((float)FRAMEWORK.GetWindowSize().x / 8),
		(float)FRAMEWORK.GetWindowSize().y });

	leftFiller->SetPosition({ 0,0 });
	rightFiller->SetPosition({ FRAMEWORK.GetWindowSize().x - rightFiller->GetSize().x, 0 });
	leftFiller->SetColor(sf::Color::Black);
	rightFiller->SetColor(sf::Color::Black);

	AddGo(leftFiller, Layers::Ui);
	AddGo(rightFiller, Layers::Ui);

	
	buildings["TerranBuilding"] = new UpgradeBuilding("terranBuilding", Building::Races::Terran);
	buildings["TerranBuilding"]->SetPosition({ 12 * 32 , 27 * 32 });
	AddGo(buildings["TerranBuilding"], Layers::World);

	buildings["ZergBuilding"] = new UpgradeBuilding("zergBuilding", Building::Races::Zerg);
	buildings["ZergBuilding"]->SetPosition({ 16 * 32 , 27 * 32 });
	AddGo(buildings["ZergBuilding"], Layers::World);
	
	buildings["ProtossBuilding"] = new UpgradeBuilding("protossBuilding", Building::Races::Protoss);
	buildings["ProtossBuilding"]->SetPosition({ 19 * 32 , 27 * 32 });
	AddGo(buildings["ProtossBuilding"], Layers::World);

	buildings["Sellbuilding"] = new SellBuilding("sellBuilding");
	buildings["Sellbuilding"]->SetPosition({ 26 * 32 , 24 * 32 });
	buildings["Sellbuilding"]->SetScale({ 0.25, 0.23});
	AddGo(buildings["Sellbuilding"], Layers::World);

	mainInterface = new Interface("Interface");

	mainInterface->sortLayer = 10;

	AddGo(mainInterface, Layers::Ui);

	spawner = new Spawner("Spawner");
	AddGo(spawner, Layers::World);

	Scene::Init();

	tileSet->LoadTileMap("tilejson/Map.json", 0.5f);
	tileSet->VaSet();

	civilian = new Civilian();

	AddGo(civilian, Layers::World);

	civilian->Init();

	civilian->SetPosition({ 27.f * 32.f + 16.f, 29.f * 32.f + 16.f });

	AllUnitList.push_back(civilian);

}

void SceneGame::Release()
{
	Scene::Release();
	
}

void SceneGame::Reset()
{
	hydraliskUpgrade = 0;
	dragoonUpgrade = 0;
	ghostUpgrade = 0;
}

void SceneGame::Enter()
{
	Scene::Enter();

}

void SceneGame::Exit()
{
	Scene::Exit();
	
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	screenPos = SCENE_MGR.GetCurrentScene()->UiToScreen((sf::Vector2f)mouse->GetPosition());
	worldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(screenPos);

	

	if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		if (!modeDeveloper)
		{
			modeDeveloper = true;
			return;
		}
		if (modeDeveloper)
		{
			modeDeveloper = false;
			return;
		}
	}

	if (modeDeveloper)
	{
		std::cout << (int)worldPos.x / 32 << " " << (int)worldPos.y / 32 << std::endl;
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Middle))
	{
		lastMouseWorldPos = worldPos;
	}

	if (InputMgr::GetMouseButton(sf::Mouse::Middle) &&
		delta != lastMouseWorldPos - worldPos)
	{
		delta = lastMouseWorldPos - worldPos; 

		GetWorldView().move(delta);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Q))
	{
		BuyUnit();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::W))
	{
		for (auto it = HydraliskList.begin(); it != HydraliskList.end();)
		{
			SCUnit* hydralisk = *it;
			hydralisk->SellThis();
			it = HydraliskList.erase(it);
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::E))
	{
		Enemy* enemy = new Enemy("snail");
		enemy->SetPosition(worldPos);
		AddGo(enemy, Layers::World);
		enemy->Init();
		EnemyList.push_back(enemy);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		for (auto it = EnemyList.begin(); it != EnemyList.end();)
		{
			Enemy* enemy = *it;
			RemoveGo(enemy);
			delete(enemy);
			it = EnemyList.erase(it);
		}
	}

}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);

	if (civilian->GetPosition().x >= 900)
	{
		civilian->SetPosition({ 27.f * 32.f + 16.f, 29.f * 32.f + 16.f });
		civilian->SetIsAster(false);
		civilian->SetStatus(SCUnit::Status::IDLE);
		BuyUnit();
	}

}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::DebugUpdate(float dt)
{
	Scene::DebugUpdate(dt);
}
	
void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::BuyUnit()
{
	int randomUnit = -1;
	randomUnit = Utils::RandomRange(0, 3);
	int randomint = -1;
	randomint = Utils::RandomRange(0, 10000);
	SCUnit::Rarity randomrarity = SCUnit::Rarity::NONE;
	if (randomint < 5000)
	{
		randomrarity = SCUnit::Rarity::Common;
	}
	if (randomint >= 5000 && randomint < 8310)
	{
		randomrarity = SCUnit::Rarity::Rare;
	}
	if (randomint >= 8310 && randomint < 9330)
	{
		randomrarity = SCUnit::Rarity::Ancient;
	}
	if (randomint >= 9330 && randomint < 9840)
	{
		randomrarity = SCUnit::Rarity::Artifact;
	}
	if (randomint >= 9840 && randomint < 9920)
	{
		randomrarity = SCUnit::Rarity::Saga;
	}
	if (randomint >= 9920 && randomint < 9970)
	{
		randomrarity = SCUnit::Rarity::Legendary;
	}
	if (randomint >= 9970 && randomint < 9988)
	{
		randomrarity = SCUnit::Rarity::Mythic;
	}
	if (randomint >= 9988 && randomint < 10000)
	{
		randomrarity = SCUnit::Rarity::Primeval;
	}

	switch (randomUnit)
	{
	case 0:
	{
		Hydralisk* hydralisk = new Hydralisk("hydralisk", randomrarity);
		hydralisk->SetPosition({ 16.f * 32.f + 16.f, 16.f * 32.f + 16.f });
		AddGo(hydralisk, Layers::World);
		hydralisk->Init();
		HydraliskList.push_back(hydralisk);
		AllUnitList.push_back(hydralisk);
		message(MessageType::BuyUnit, SCUnit::Type::Hydralisk, randomrarity);
	}
	break;
	case 1:
	{
		Dragoon* dragoon = new Dragoon("dragoon", randomrarity);
		dragoon->SetPosition({ 16.f * 32.f + 16.f, 16.f * 32.f + 16.f });
		AddGo(dragoon, Layers::World);
		dragoon->Init();
		DragoonList.push_back(dragoon);
		AllUnitList.push_back(dragoon);
		message(MessageType::BuyUnit, SCUnit::Type::Dragoon, randomrarity);
	}
	break;
	case 2:
	{
		Ghost* ghost = new Ghost("ghost", randomrarity);
		ghost->SetPosition({ 16.f * 32.f + 16.f, 16.f * 32.f + 16.f });
		AddGo(ghost, Layers::World);
		ghost->Init();
		GhostList.push_back(ghost);
		AllUnitList.push_back(ghost);
		message(MessageType::BuyUnit, SCUnit::Type::Ghost, randomrarity);
	}
	break;
	default:
		break;
	}
}
