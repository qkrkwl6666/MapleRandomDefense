#include "pch.h"
#include "Interface.h"
#include "SpriteGo.h"
#include "Crosshair.h"
#include "SceneGame.h"
#include "Building.h"
#include "UpgradeBuilding.h"
#include "SellBuilding.h"

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

	buildings = dynamic_cast<SceneGame*>
		(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetBuildings();

	// 업그레이드 이미지
	NewSpriteGo("HydraliskUpgrade", "graphics/UI/Interface/HydraliskUpgrade.png");
	sprites["HydraliskUpgrade"]->SetOrigin(Origins::TL);
	sprites["HydraliskUpgrade"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["HydraliskUpgrade"]->sortLayer = 11;
	sprites["HydraliskUpgrade"]->SetActive(false);

	NewSpriteGo("DragoonUpgrade", "graphics/UI/Interface/DragoonUpgrade.png");
	sprites["DragoonUpgrade"]->SetOrigin(Origins::TL);
	sprites["DragoonUpgrade"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["DragoonUpgrade"]->sortLayer = 11;
	sprites["DragoonUpgrade"]->SetActive(false);

	NewSpriteGo("GhostUpgrade", "graphics/UI/Interface/GhostUpgrade.png");
	sprites["GhostUpgrade"]->SetOrigin(Origins::TL);
	sprites["GhostUpgrade"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["GhostUpgrade"]->sortLayer = 11;
	sprites["GhostUpgrade"]->SetActive(false);

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
		noUnits = true;
		for (SCUnit* scUnit : isSelectList)
		{
			scUnit->SetSelect(false);
		}
		isSelectList.clear();

		isSelecting = false;
		selectBox->SetActive(false);

		// 유닛 검사
		std::list<SCUnit*> allUnit = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetAllUnitList();
		for (SCUnit* scUnit : allUnit)
		{
			if (selectBox->GetGlobalBounds().contains(scUnit->GetPosition()))
			{
				SetActiveUpgrade(false);
				noUnits = false;
				isSelectList.push_back(scUnit);
				scUnit->SetSelect(true);
			}
		}

		// 건물 검사 유닛 없을때만
		if (noUnits)
		{
			for (const auto& pair : buildings)
			{
				Building* building = pair.second;
				if (building->GetGlobalBounds().contains(selectBox->GetPosition()))
				{
					SetActiveUpgrade(false);
					switch (building->GetBuildingType())
					{
					case Building::BuildingType::UPGRADE:
						{
						UpgradeBuilding* Up = dynamic_cast<UpgradeBuilding*>(building);
							switch (Up->GetRace())
							{
							case Building::Races::Zerg:
								sprites["HydraliskUpgrade"]->SetActive(true);
								Up->SetSelect(true);
								return;
								break;
							case Building::Races::Terran:
								sprites["GhostUpgrade"]->SetActive(true);
								Up->SetSelect(true);
								return;
								break;
							case Building::Races::Protoss:
								sprites["DragoonUpgrade"]->SetActive(true);
								Up->SetSelect(true);
								return;
								break;
							}
							break;
						}
					case Building::BuildingType::SELL:

						break;
					}
				}
			}
		}

	}

	if (isSelecting)
	{
		selectBox->SetSize(worldMousePos - selectStartPos);
	}

	// 건물 업그레이드 상호작용
	if (sprites["HydraliskUpgrade"]->GetActive() && sprites["HydraliskUpgrade"]->
		GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) && 
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << "HydraliskUpgrade!!" << std::endl;
		Upgrade();
	}

	else if (sprites["GhostUpgrade"]->GetActive() &&
		sprites["GhostUpgrade"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << "GhostUpgrade!!" << std::endl;
		Upgrade();
	}

	else if (sprites["DragoonUpgrade"]->GetActive() &&
		sprites["DragoonUpgrade"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << "DragoonUpgrade!!" << std::endl;
		Upgrade();
	}
	
}

void Interface::LateUpdate(float dt)
{
	UIGo::LateUpdate(dt);
}

void Interface::SetActiveUpgrade(bool active)
{
	sprites["HydraliskUpgrade"]->SetActive(active);
	sprites["DragoonUpgrade"]->SetActive(active);
	sprites["GhostUpgrade"]->SetActive(active);

	for (auto& data : buildings)
	{
		data.second->SetSelect(active);
	}
}

void Interface::Upgrade()
{
	for (auto& data : buildings)
	{
		if (data.second->GetSelect())
		{
			UpgradeBuilding* up = dynamic_cast<UpgradeBuilding*>
				(data.second);
			up->Upgrade();
		}
	}
}
