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

	// 판매 이미지
	NewSpriteGo("GhostSell", "graphics/UI/Interface/GhostSell.png");
	sprites["GhostSell"]->SetOrigin(Origins::TL);
	sprites["GhostSell"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["GhostSell"]->sortLayer = 11;
	sprites["GhostSell"]->SetActive(false);
	sprites["GhostSell"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("HydraliskSell", "graphics/UI/Interface/HydraliskSell.png");
	sprites["HydraliskSell"]->SetOrigin(Origins::TL);
	sprites["HydraliskSell"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.77f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["HydraliskSell"]->sortLayer = 11;
	sprites["HydraliskSell"]->SetActive(false);
	sprites["HydraliskSell"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("DragoonSell", "graphics/UI/Interface/DragoonSell.png");
	sprites["DragoonSell"]->SetOrigin(Origins::TL);
	sprites["DragoonSell"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.823f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["DragoonSell"]->sortLayer = 11;
	sprites["DragoonSell"]->SetActive(false);
	sprites["DragoonSell"]->SetScale({ 0.75f, 0.75f });
	
	// 판매 상세
	NewSpriteGo("HydraliskNormal", "graphics/UI/Interface/HydraliskSellNoHave.png");
	sprites["HydraliskNormal"]->SetOrigin(Origins::TL);
	sprites["HydraliskNormal"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["HydraliskNormal"]->sortLayer = 11;
	sprites["HydraliskNormal"]->SetActive(false);
	sprites["HydraliskNormal"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("HydraliskRare", "graphics/UI/Interface/HydraliskSellNoHave.png");
	sprites["HydraliskRare"]->SetOrigin(Origins::TL);
	sprites["HydraliskRare"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.77f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["HydraliskRare"]->sortLayer = 11;
	sprites["HydraliskRare"]->SetActive(false);
	sprites["HydraliskRare"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("HydraliskAncient", "graphics/UI/Interface/HydraliskSellNoHave.png");
	sprites["HydraliskAncient"]->SetOrigin(Origins::TL);
	sprites["HydraliskAncient"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.823f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["HydraliskAncient"]->sortLayer = 11;
	sprites["HydraliskAncient"]->SetActive(false);
	sprites["HydraliskAncient"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("HydraliskArtifact", "graphics/UI/Interface/HydraliskSellNoHave.png");
	sprites["HydraliskArtifact"]->SetOrigin(Origins::TL);
	sprites["HydraliskArtifact"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.83f });
	sprites["HydraliskArtifact"]->sortLayer = 11;
	sprites["HydraliskArtifact"]->SetActive(false);
	sprites["HydraliskArtifact"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("HydraliskNarrative", "graphics/UI/Interface/HydraliskSellNoHave.png");
	sprites["HydraliskNarrative"]->SetOrigin(Origins::TL);
	sprites["HydraliskNarrative"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.77f , FRAMEWORK.GetWindowSize().y * 0.83f });
	sprites["HydraliskNarrative"]->sortLayer = 11;
	sprites["HydraliskNarrative"]->SetActive(false);
	sprites["HydraliskNarrative"]->SetScale({ 0.75f, 0.75f });

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
				SetActiveSell(false);
				SetActiveSellInfo(false);
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
					SetActiveSellInfo(false);
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
						{
							SetActiveSell(true);
						}
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

	// 판매 건물 상호작용
	if (sprites["GhostSell"]->GetActive() && sprites["GhostSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << "GhostSell!!" << std::endl;

	}
	else if (sprites["HydraliskSell"]->GetActive() &&
		sprites["HydraliskSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << "HydraliskSell!!" << std::endl;
		SetActiveSellInfo(true);
		sprites["GhostSell"]->SetActive(false);
		sprites["HydraliskSell"]->SetActive(false);
		sprites["DragoonSell"]->SetActive(false);
	}
		else if (sprites["DragoonSell"]->GetActive() &&
		sprites["DragoonSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << "DragoonSell!!" << std::endl;

	}

	HydraliskSellUpdate();

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

void Interface::SetActiveSell(bool active)
{
	sprites["GhostSell"]->SetActive(active);
	sprites["HydraliskSell"]->SetActive(active);
	sprites["DragoonSell"]->SetActive(active);

	for (auto& data : buildings)
	{
		if (data.second->GetBuildingType() == Building::BuildingType::SELL)
		{
			data.second->SetSelect(active);
		}
	}
}

void Interface::SetActiveSellInfo(bool active)
{
	sprites["HydraliskNormal"]->SetActive(active);
	sprites["HydraliskRare"]->SetActive(active);
	sprites["HydraliskAncient"]->SetActive(active);
	sprites["HydraliskArtifact"]->SetActive(active);
	sprites["HydraliskNarrative"]->SetActive(active);
}

void Interface::HydraliskSellUpdate()
{
	if (sprites["HydraliskNormal"]->GetActive() &&
		sprites["HydraliskNormal"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Hydralisk, SCUnit::Rarity::Common);
			}
		}
	}

	else if (sprites["HydraliskRare"]->GetActive() &&
		sprites["HydraliskRare"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Hydralisk, SCUnit::Rarity::Rare);
			}
		}
	}


	else if (sprites["HydraliskAncient"]->GetActive() &&
		sprites["HydraliskAncient"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Hydralisk, SCUnit::Rarity::Ancient);
			}
		}
	}

	else if (sprites["HydraliskArtifact"]->GetActive() &&
		sprites["HydraliskArtifact"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Hydralisk, SCUnit::Rarity::Artifact);
			}
		}
	}

	else if (sprites["HydraliskNarrative"]->GetActive() &&
		sprites["HydraliskNarrative"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Hydralisk, SCUnit::Rarity::Saga);
			}
		}
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
