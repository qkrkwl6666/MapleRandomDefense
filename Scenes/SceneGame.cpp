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
			SCUnit* hydralisk = dynamic_cast<SCUnit*>(*it);
			if (hydralisk && hydralisk->GetRarity() == r)
			{
				HydraliskList.erase(it);
				hydralisk->SellThis();
				return;
			}
		}
		break;
	case SCUnit::Type::Dragoon:
		for (auto it = DragoonList.begin(); it != DragoonList.end();)
		{
			SCUnit* dragoon = dynamic_cast<SCUnit*>(*it);
			if (dragoon && dragoon->GetRarity() == r)
			{
				DragoonList.erase(it);
				dragoon->SellThis();
				return;
			}
		}
		break;
	case SCUnit::Type::Ghost:
		for (auto it = GhostList.begin(); it != GhostList.end();)
		{
			SCUnit* ghost = dynamic_cast<SCUnit*>(*it);
			if (ghost && ghost->GetRarity() == r)
			{
				GhostList.erase(it);
				ghost->SellThis();
				return;
			}
		}
		break;
	default:
		break;
	}
	std::cout << "À¯´Ö ¾øÀ½" << std::endl;
}

void SceneGame::message(MessageType m)
{
	switch (m)
	{
	case SceneGame::MessageType::NONE:
		break;
	case SceneGame::MessageType::NotEnoughMinerals:
		std::cout << "¹Ì³×¶ö ºÎÁ·" << std::endl;
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
		type = "È÷µå¶ó ";
		break;
	case SCUnit::Type::Dragoon:
		type = "µå¶ó±º ";
		break;
	case SCUnit::Type::Ghost:
		type = "°í½ºÆ® ";
		break;
	default:
		break;
	}

	std::string rarity;
	switch (r)
	{
	case SCUnit::Rarity::Common:
		rarity = "ÀÏ¹Ý]";
		break;
	case SCUnit::Rarity::Rare:
		rarity = "·¹¾î]";
		break;
	case SCUnit::Rarity::Ancient:
		rarity = "°í´ë]";
		break;
	case SCUnit::Rarity::Artifact:
		rarity = "À¯¹°]";
		break;
	case SCUnit::Rarity::Saga:
		rarity = "¼­»ç]";
		break;
	}

	switch (m)
	{
	case SceneGame::MessageType::BuyUnit:
		std::cout << "[: " << type << rarity << std::endl;
		break;
	case SceneGame::MessageType::SellUnit:
		std::cout << "[À¯´ÖÀ» ÆÇ¸ÅÇß½À´Ï´Ù : " << type << rarity << std::endl;
		break;
	default:
		break;
	}
}


void SceneGame::message(int i)
{
	std::cout << "+ " << i << "¿ø" << std::endl;
}

void SceneGame::UpgradeUpdate()
{
	for (auto go : HydraliskList)
	{
		SCUnit* hydralisk = dynamic_cast<SCUnit*>(go);
		hydralisk->SetUpgrade(hydraliskUpgrade);
	}

	for (auto go : GhostList)
	{
		SCUnit* ghost = dynamic_cast<SCUnit*>(go);
		ghost->SetUpgrade(ghostUpgrade);
	}

	for (auto go : DragoonList)
	{
		SCUnit* dragoon = dynamic_cast<SCUnit*>(go);
		dragoon->SetUpgrade(dragoonUpgrade);
	}
}

void SceneGame::Init()
{
	tileSet = new TileSet();
	AddGo(tileSet, Scene::World);

	mouse = FRAMEWORK.GetMouse();

	mainInterface = new Interface("Interface");

	mainInterface->sortLayer = 10;

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

	AddGo(mainInterface, Layers::Ui);


	UpgradeBuilding* TerranBuilding = new UpgradeBuilding("terranBuilding", Building::Races::Terran);
	TerranBuilding->SetPosition({ 12 * 32 , 27 * 32 });
	AddGo(TerranBuilding, Layers::World);

	UpgradeBuilding* ZergBuilding = new UpgradeBuilding("zergBuilding", Building::Races::Zerg);
	ZergBuilding->SetPosition({ 16 * 32 , 27 * 32 });
	AddGo(ZergBuilding, Layers::World);

	UpgradeBuilding* ProtossBuilding = new UpgradeBuilding("protossBuilding", Building::Races::Protoss);
	ProtossBuilding->SetPosition({ 19 * 32 , 27 * 32 });
	AddGo(ProtossBuilding, Layers::World);

	SellBuilding* sellbuilding = new SellBuilding("sellBuilding");
	sellbuilding->SetPosition({ 26 * 32 , 24 * 32 });
	sellbuilding->SetScale({ 0.25, 0.23});
	AddGo(sellbuilding, Layers::World);

	Scene::Init();

	tileSet->LoadTileMap("tilejson/Map.json", 0.5f);
	tileSet->VaSet();
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

	FindGoAll("hydralisk", HydraliskList, Scene::Layers::World);
	FindGoAll("dragoon", DragoonList, Scene::Layers::World);
	FindGoAll("ghost", GhostList, Scene::Layers::World);

	std::cout << (int)worldPos.x / 32 << " " << (int)worldPos.y / 32 << std::endl;

	//ï¿½ï¿½ï¿½ì½ºï¿½ï¿½ ï¿½ï¿½ ï¿½Ìµï¿½

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Middle))
	{
		lastMouseWorldPos = worldPos; // ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ì½º ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Õ´Ï´ï¿½.
	}

	// ï¿½ï¿½ï¿½ì½º ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ deltaï¿½ï¿½ ï¿½ï¿½Ä¡ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	if (InputMgr::GetMouseButton(sf::Mouse::Middle) &&
		delta != lastMouseWorldPos - worldPos)
	{
		delta = lastMouseWorldPos - worldPos; // ï¿½Ìµï¿½ï¿½ï¿½.

		GetWorldView().move(delta);
	}

	// Å¸ï¿½ï¿½ ï¿½Ì±ï¿½ - ï¿½ï¿½ ï¿½ï¿½ ï¿½Ï³ï¿½
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		ShapeGo<sf::CircleShape>* tower = new ShapeGo<sf::CircleShape>("tower");
		int randomTower = -1;
		randomTower = Utils::RandomRange(0, 1);
		int randomint = -1;
		randomint = Utils::RandomRange(0, 5);
		SCUnit::Rarity randomrarity = static_cast<SCUnit::Rarity>(randomint);
		switch (randomTower)
		{
		case 0:
		{
			Hydralisk* hydralisk = new Hydralisk("hydralisk",randomrarity);
			hydralisk->SetPosition(worldPos);
			AddGo(hydralisk, Layers::World);
			HydraliskList.push_back(hydralisk);
			message(MessageType::BuyUnit, SCUnit::Type::Hydralisk, randomrarity);
		}
			break;
		case 1:
			tower->SetColor(sf::Color::Red);
			tower->SetSize({ 15,0 });
			tower->SetOrigin(Origins::MC);
			tower->SetOutlineThickness(2.f);
			tower->SetOutlineColor(sf::Color::Black);
			tower->SetPosition(worldPos);
			AddGo(tower, Layers::World);
			break;
		case 2:
			tower->SetColor(sf::Color::Blue);
			tower->SetSize({ 15,0 });
			tower->SetOrigin(Origins::MC);
			tower->SetOutlineThickness(2.f);
			tower->SetOutlineColor(sf::Color::Black);
			tower->SetPosition(worldPos);
			AddGo(tower, Layers::World);
			break;
		default:
			break;
		}
	}

}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
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