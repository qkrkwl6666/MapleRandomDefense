#include "pch.h"
#include "Scene.h"
#include "SceneGame.h"
#include "TileSet.h"
#include "ShapeGo.h"
#include <Windows.h>
#include "Crosshair.h"
#include "UpgradeBuilding.h"
#include "SCUnit.h"


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
			}
		}
		break;
	default:
		break;
	}
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
	}

	std::cout << "[유닛을 판매했습니다 : " << type << rarity << std::endl;
}

void SceneGame::message(int i)
{
	std::cout << "+ " << i << "원" << std::endl;
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
	tileSet->LoadTileMap("tilejson/Map.json", 0.5f);
	tileSet->VaSet();
	mouse = FRAMEWORK.GetMouse();

	leftFiller = new ShapeGo<sf::RectangleShape>("leftFiller");
	rightFiller = new ShapeGo<sf::RectangleShape>("rightFiller");

	worldView.setSize(1365.33, 768);
	leftFiller->SetSize({ (FRAMEWORK.GetWindowSize().x - worldView.getSize().x) / 4, (float) FRAMEWORK.GetWindowSize().y });
	rightFiller->SetSize({ (FRAMEWORK.GetWindowSize().x - worldView.getSize().x) / 4, (float)FRAMEWORK.GetWindowSize().y });
	leftFiller->SetPosition({ 0,0 });
	rightFiller->SetPosition({ FRAMEWORK.GetWindowSize().x - rightFiller->GetSize().x, 0 });
	leftFiller->SetColor(sf::Color::Black);
	rightFiller->SetColor(sf::Color::Black);
	AddGo(leftFiller, Layers::Ui);
	AddGo(rightFiller, Layers::Ui);

	UpgradeBuilding* TerranBuilding = new UpgradeBuilding("terranBuilding", Building::Races::Terran);
	TerranBuilding->Init();
	TerranBuilding->SetPosition({ 12 * 32 , 27 * 32 });
	AddGo(TerranBuilding, Layers::World);

	UpgradeBuilding* ZergBuilding = new UpgradeBuilding("zergBuilding", Building::Races::Zerg);
	ZergBuilding->Init();
	ZergBuilding->SetPosition({ 16 * 32 , 27 * 32 });
	AddGo(ZergBuilding, Layers::World);

	UpgradeBuilding* ProtossBuilding = new UpgradeBuilding("protossBuilding", Building::Races::Protoss);
	ProtossBuilding->Init();
	ProtossBuilding->SetPosition({ 19 * 32 , 27 * 32 });
	AddGo(ProtossBuilding, Layers::World);
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

	//마우스로 뷰 이동

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Middle))
	{
		lastMouseWorldPos = worldPos; // 현재 마우스 위치를 저장합니다.
	}

	// 마우스 휠이 눌린 상태 유지 전에 delta랑 위치가 같지 않을때만
	if (InputMgr::GetMouseButton(sf::Mouse::Middle) &&
		delta != lastMouseWorldPos - worldPos)
	{
		delta = lastMouseWorldPos - worldPos; // 이동량.

		GetWorldView().move(delta);
	}

	// 타워 뽑기 - 셋 중 하나
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		ShapeGo<sf::CircleShape>* tower = new ShapeGo<sf::CircleShape>("tower");
		int randomTower = -1;
		randomTower = Utils::RandomRange(0, 3);

		switch (randomTower)
		{
		case 0:
			tower->SetColor(sf::Color::White);
			tower->SetSize({ 15,0 });
			tower->SetOrigin(Origins::MC);
			tower->SetOutlineThickness(2.f);
			tower->SetOutlineColor(sf::Color::Black);
			tower->SetPosition(worldPos);
			AddGo(tower, Layers::World);
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