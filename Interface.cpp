#include "pch.h"
#include "Interface.h"
#include "SpriteGo.h"
#include "Crosshair.h"
#include "SceneGame.h"

Interface::Interface(const std::string& name)
{

}

Interface::~Interface()
{

}

void Interface::Init()
{

	// 메인 인터페이스
	NewSpriteGo("MainInterface", "graphics/UI/Interface/Interface.png");
	sprites["MainInterface"]->SetOrigin(Origins::BC);
	sprites["MainInterface"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.5f , static_cast<float>(FRAMEWORK.GetWindowSize().y), });
	sprites["MainInterface"]->SetScale({ 1.0f , 1.0f });
	sprites["MainInterface"]->sortLayer = 10;

	// 미네랄 
	NewSpriteGo("minerals", "graphics/UI/Interface/minerals.png");
	sprites["minerals"]->SetOrigin(Origins::MC);
	sprites["minerals"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
		0.68f , FRAMEWORK.GetWindowSize().y * 0.02f });
	sprites["minerals"]->SetScale({ 1.0f , 1.0f });
	sprites["minerals"]->sortLayer = 10;

	// 가스
	NewSpriteGo("VespeneGas", "graphics/UI/Interface/VespeneGas.png");
	sprites["VespeneGas"]->SetOrigin(Origins::MC);
	sprites["VespeneGas"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.78f , FRAMEWORK.GetWindowSize().y * 0.02f });
	sprites["VespeneGas"]->SetScale({ 1.0f , 1.0f });
	sprites["VespeneGas"]->sortLayer = 10;

	selectBox = new ShapeGo<sf::RectangleShape>("SelectBox");

	selectBox->SetColor(sf::Color::Transparent);
	selectBox->SetOutlineColor(sf::Color::Green);
	selectBox->SetOutlineThickness(0.6f);

	SCENE_MGR.GetScene(SceneIds::SceneGame)->AddGo(selectBox, Scene::World);

	UiInit();
	ObjectsSort();
}

void Interface::Release()
{
	UIGo::Release();

}

void Interface::Reset()
{
	UIGo::Reset();
}

void Interface::Update(float dt)
{
	UIGo::Update(dt);

	worldMousePos = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos();

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && !isSelecting)
	{
		isSelecting = true;

		selectStartPos = worldMousePos;
		selectBox->SetActive(true);

		selectBox->SetPosition(selectStartPos); // 시작 위치
	}

	else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isSelecting)
	{
		isSelecting = false;
		selectBox->SetActive(false);
		
		std::cout << selectBox->GetGlobalBounds().left << 
			" " << selectBox->GetGlobalBounds().top << std::endl;
	}

	if (isSelecting)
	{
		selectBox->SetSize(worldMousePos - selectStartPos);

	}
}

void Interface::LateUpdate(float dt)
{
	UIGo::LateUpdate(dt);
}
