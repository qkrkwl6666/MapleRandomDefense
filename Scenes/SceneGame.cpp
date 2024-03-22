#include "pch.h"
#include "Scene.h"
#include "SceneGame.h"
#include "TileSet.h"
#include "ShapeGo.h"
#include <Windows.h>
#include "Crosshair.h"
#include "Interface.h"


SceneGame::SceneGame(SceneIds id) : Scene(id)
{

}

void SceneGame::Init()
{
	tileSet = new TileSet();
	AddGo(tileSet, Scene::World);
	tileSet->LoadTileMap("tilejson/Map.json", 0.5f);
	tileSet->VaSet();
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

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
	
}

void SceneGame::Reset()
{
	
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