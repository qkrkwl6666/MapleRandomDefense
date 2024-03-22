#include "pch.h"
#include "Scene.h"
#include "SceneGame.h"
#include "TileSet.h"
#include "ShapeGo.h"
#include <Windows.h>
#include "Crosshair.h"
#include "Interface.h"
#include "UpgradeBuilding.h"
#include "SCUnit.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{

}


void SceneGame::message(MessageType m)
{
	switch (m)
	{
	case SceneGame::MessageType::NONE:
		break;
	case SceneGame::MessageType::NotEnoughMinerals:
		std::cout << "�̳׶� ����" << std::endl;
		break;
	case SceneGame::MessageType::count:
		break;
	default:
		break;
	}
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

	//���콺�� �� �̵�

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Middle))
	{
		lastMouseWorldPos = worldPos; // ���� ���콺 ��ġ�� �����մϴ�.
	}

	// ���콺 ���� ���� ���� ���� ���� delta�� ��ġ�� ���� ��������
	if (InputMgr::GetMouseButton(sf::Mouse::Middle) &&
		delta != lastMouseWorldPos - worldPos)
	{
		delta = lastMouseWorldPos - worldPos; // �̵���.

		GetWorldView().move(delta);
	}

	// Ÿ�� �̱� - �� �� �ϳ�
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