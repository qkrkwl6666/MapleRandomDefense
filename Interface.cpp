#include "pch.h"
#include "Interface.h"
#include "SpriteGo.h"
#include "TextGo.h"
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
	// ****************** 히드라 5종

	NewSpriteGo("DragoonNormal", "graphics/UI/Interface/DragoonSellNoHave.png");
	sprites["DragoonNormal"]->SetOrigin(Origins::TL);
	sprites["DragoonNormal"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["DragoonNormal"]->sortLayer = 11;
	sprites["DragoonNormal"]->SetActive(false);
	sprites["DragoonNormal"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("DragoonRare", "graphics/UI/Interface/DragoonSellNoHave.png");
	sprites["DragoonRare"]->SetOrigin(Origins::TL);
	sprites["DragoonRare"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.77f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["DragoonRare"]->sortLayer = 11;
	sprites["DragoonRare"]->SetActive(false);
	sprites["DragoonRare"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("DragoonAncient", "graphics/UI/Interface/DragoonSellNoHave.png");
	sprites["DragoonAncient"]->SetOrigin(Origins::TL);
	sprites["DragoonAncient"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.823f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["DragoonAncient"]->sortLayer = 11;
	sprites["DragoonAncient"]->SetActive(false);
	sprites["DragoonAncient"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("DragoonArtifact", "graphics/UI/Interface/DragoonSellNoHave.png");
	sprites["DragoonArtifact"]->SetOrigin(Origins::TL);
	sprites["DragoonArtifact"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.83f });
	sprites["DragoonArtifact"]->sortLayer = 11;
	sprites["DragoonArtifact"]->SetActive(false);
	sprites["DragoonArtifact"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("DragoonNarrative", "graphics/UI/Interface/DragoonSellNoHave.png");
	sprites["DragoonNarrative"]->SetOrigin(Origins::TL);
	sprites["DragoonNarrative"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.77f , FRAMEWORK.GetWindowSize().y * 0.83f });
	sprites["DragoonNarrative"]->sortLayer = 11;
	sprites["DragoonNarrative"]->SetActive(false);
	sprites["DragoonNarrative"]->SetScale({ 0.75f, 0.75f });
	//******************** 드라군 5종

	NewSpriteGo("GhostNormal", "graphics/UI/Interface/GhostSellNoHave.png");
	sprites["GhostNormal"]->SetOrigin(Origins::TL);
	sprites["GhostNormal"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["GhostNormal"]->sortLayer = 11;
	sprites["GhostNormal"]->SetActive(false);
	sprites["GhostNormal"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("GhostRare", "graphics/UI/Interface/GhostSellNoHave.png");
	sprites["GhostRare"]->SetOrigin(Origins::TL);
	sprites["GhostRare"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.77f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["GhostRare"]->sortLayer = 11;
	sprites["GhostRare"]->SetActive(false);
	sprites["GhostRare"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("GhostAncient", "graphics/UI/Interface/GhostSellNoHave.png");
	sprites["GhostAncient"]->SetOrigin(Origins::TL);
	sprites["GhostAncient"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.823f , FRAMEWORK.GetWindowSize().y * 0.745f });
	sprites["GhostAncient"]->sortLayer = 11;
	sprites["GhostAncient"]->SetActive(false);
	sprites["GhostAncient"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("GhostArtifact", "graphics/UI/Interface/GhostSellNoHave.png");
	sprites["GhostArtifact"]->SetOrigin(Origins::TL);
	sprites["GhostArtifact"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.716f , FRAMEWORK.GetWindowSize().y * 0.83f });
	sprites["GhostArtifact"]->sortLayer = 11;
	sprites["GhostArtifact"]->SetActive(false);
	sprites["GhostArtifact"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("GhostNarrative", "graphics/UI/Interface/GhostSellNoHave.png");
	sprites["GhostNarrative"]->SetOrigin(Origins::TL);
	sprites["GhostNarrative"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.77f , FRAMEWORK.GetWindowSize().y * 0.83f });
	sprites["GhostNarrative"]->sortLayer = 11;
	sprites["GhostNarrative"]->SetActive(false);
	sprites["GhostNarrative"]->SetScale({ 0.75f, 0.75f });

	NewSpriteGo("Warframe", "graphics/UI/Interface/DragoonWarframe.png");
	sprites["Warframe"]->SetOrigin(Origins::TL);
	sprites["Warframe"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.33f , FRAMEWORK.GetWindowSize().y * 0.84f });
	sprites["Warframe"]->sortLayer = 11;
	sprites["Warframe"]->SetActive(false);
	sprites["Warframe"]->SetScale({ 1.3f, 1.3f });

	warframeName.setCharacterSize(20);
	warframeName.setFont(RES_MGR_FONT.Get("font/Kostar.ttf"));
	warframeName.setPosition({ FRAMEWORK.GetWindowSize().x *
		0.45f , FRAMEWORK.GetWindowSize().y * 0.81f });
	warframeName << sf::Color::White;

	NewTextGo("UIAttackType", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶폭발형", 20, sf::Color::White);
	texts["UIAttackType"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.46f , FRAMEWORK.GetWindowSize().y * 0.85f });
	texts["UIAttackType"]->sortLayer = 11;
	texts["UIAttackType"]->SetActive(false);

	// 타이머 
	NewTextGo("UITimer", RES_MGR_FONT.Get("font/Kostar.ttf"), L"", 20, sf::Color::White);
	texts["UITimer"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.5f , FRAMEWORK.GetWindowSize().y * 0.05f });
	texts["UITimer"]->sortLayer = 13;
	texts["UITimer"]->SetString(uiTimerString);
	texts["UITimer"]->SetColor(sf::Color::Green);
	texts["UITimer"]->SetCharacterSize(30);
	texts["UITimer"]->SetOrigin(Origins::MC);

	NewTextGo("currentStage", RES_MGR_FONT.Get("font/Kostar.ttf"), L"현재 스테이지 : ", 20, sf::Color::White);
	texts["currentStage"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.5f , FRAMEWORK.GetWindowSize().y * 0.6f });
	texts["currentStage"]->sortLayer = 13;
	texts["currentStage"]->SetColor(sf::Color::Green);
	texts["currentStage"]->SetCharacterSize(30);
	texts["currentStage"]->SetOrigin(Origins::MC);
	texts["currentStage"]->SetActive(false);

	// 클리어 메세지 
	NewTextGo("TextClear", RES_MGR_FONT.Get("font/Kostar.ttf"), L"메이플 운빨 디펜스", 30, sf::Color::Blue);
	texts["TextClear"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.5f , FRAMEWORK.GetWindowSize().y * 0.4f });
	texts["TextClear"]->sortLayer = 15;
	texts["TextClear"]->SetOrigin(Origins::MC);
	texts["TextClear"]->SetActive(false);

	NewTextGo("TextClear1", RES_MGR_FONT.Get("font/Kostar.ttf"), L"보스 스테이지 *클리어*", 30, sf::Color::Red);
	texts["TextClear1"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.5f , FRAMEWORK.GetWindowSize().y * 0.45f });
	texts["TextClear1"]->sortLayer = 15;
	texts["TextClear1"]->SetOrigin(Origins::MC);
	texts["TextClear1"]->SetActive(false);

	NewSpriteGo("GhostUpgradeInfo", "graphics/UI/Interface/GhostUpgradeInfo.png");
	sprites["GhostUpgradeInfo"]->SetOrigin(Origins::TL);
	sprites["GhostUpgradeInfo"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.46f , FRAMEWORK.GetWindowSize().y * 0.91f });
	sprites["GhostUpgradeInfo"]->sortLayer = 11;
	sprites["GhostUpgradeInfo"]->SetActive(false);
	sprites["GhostUpgradeInfo"]->SetScale({ 0.8f, 0.8f });
	NewSpriteGo("DragoonUpgradeInfo", "graphics/UI/Interface/DragoonUpgradeInfo.png");
	sprites["DragoonUpgradeInfo"]->SetOrigin(Origins::TL);
	sprites["DragoonUpgradeInfo"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.46f , FRAMEWORK.GetWindowSize().y * 0.91f });
	sprites["DragoonUpgradeInfo"]->sortLayer = 11;
	sprites["DragoonUpgradeInfo"]->SetActive(false);
	sprites["DragoonUpgradeInfo"]->SetScale({ 0.8f, 0.8f });
	NewSpriteGo("HydraliskUpgradeInfo", "graphics/UI/Interface/HydraliskUpgradeInfo.png");
	sprites["HydraliskUpgradeInfo"]->SetOrigin(Origins::TL);
	sprites["HydraliskUpgradeInfo"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.46f , FRAMEWORK.GetWindowSize().y * 0.91f });
	sprites["HydraliskUpgradeInfo"]->sortLayer = 11;
	sprites["HydraliskUpgradeInfo"]->SetActive(false);
	sprites["HydraliskUpgradeInfo"]->SetScale({ 0.8f, 0.8f });

	NewSpriteGo("DamageInfo", "graphics/UI/Interface/UiInfo.png");
	sprites["DamageInfo"]->SetOrigin(Origins::BL);
	sprites["DamageInfo"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.49f , FRAMEWORK.GetWindowSize().y * 0.95f });
	sprites["DamageInfo"]->sortLayer = 14;
	sprites["DamageInfo"]->SetActive(false);
	sprites["DamageInfo"]->SetScale({ 1.f, 1.f });
	NewTextGo("WeaponName", RES_MGR_FONT.Get("font/Kostar.ttf"), L"Cast Optical Flare", 18, sf::Color::White);
	texts["WeaponName"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.50f , FRAMEWORK.GetWindowSize().y * 0.76f });
	texts["WeaponName"]->sortLayer = 14;
	texts["WeaponName"]->SetActive(false);
	NewTextGo("WeaponInterval", RES_MGR_FONT.Get("font/Kostar.ttf"), L"공격속도 : ", 18, sf::Color::White);
	texts["WeaponInterval"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.50f , FRAMEWORK.GetWindowSize().y * 0.795f });
	texts["WeaponInterval"]->sortLayer = 14;
	texts["WeaponInterval"]->SetActive(false);
	NewTextGo("WeaponMethod", RES_MGR_FONT.Get("font/Kostar.ttf"), L"공격방식 : ", 18, sf::Color::White);
	texts["WeaponMethod"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.50f , FRAMEWORK.GetWindowSize().y * 0.830f });
	texts["WeaponMethod"]->sortLayer = 14;
	texts["WeaponMethod"]->SetActive(false);
	NewTextGo("WeaponRange", RES_MGR_FONT.Get("font/Kostar.ttf"), L"사거리 : ", 18, sf::Color::White);
	texts["WeaponRange"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.50f , FRAMEWORK.GetWindowSize().y * 0.865f });
	texts["WeaponRange"]->sortLayer = 14;
	texts["WeaponRange"]->SetActive(false);
	NewTextGo("WeaponDamage", RES_MGR_FONT.Get("font/Kostar.ttf"), L"Damage : ", 18, sf::Color::White);
	texts["WeaponDamage"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.50f , FRAMEWORK.GetWindowSize().y * 0.90f });
	texts["WeaponDamage"]->sortLayer = 14;
	texts["WeaponDamage"]->SetActive(false);

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

	if (InputMgr::GetKeyDown(sf::Keyboard::F1))
	{
		FRAMEWORK.SetTimeScale(1.f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		FRAMEWORK.SetTimeScale(2.f);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F3))
	{
		FRAMEWORK.SetTimeScale(4.f);
	}

	// ******************타이머 && nextStage******************
	uiTimer += dt;
	currentStageTimer += dt;

	if (uiTimer >= 1.f)
	{
		gameTimer--;
		if (gameTimer >= 10)
		{
			uiTimerString.replace(3, std::string::npos, std::to_string(gameTimer));
		}
		else
		{
			if (gameTimer < 0 && min >= 1)
			{
				min--;
				gameTimer = 59;
				uiTimerString.replace(0, 2, "0" + std::to_string(min));
				uiTimerString.replace(3, std::string::npos, std::to_string(gameTimer));
			}
			else if (gameTimer < 0 && min <= 0)
			{
				// 다음 스테이지
				currentStage++;

				if (currentStage == 14)
				{
					min = 5;
					gameTimer = 20;
					uiTimerString = "05:20";
				}
				else
				{
					min = 2;
					gameTimer = 20;
					uiTimerString = "02:20";

					texts["currentStage"]->SetString(L"현재 스테이지 : " + Utils::CP949ToWString(std::to_string(currentStage)));
					texts["currentStage"]->SetActive(true);
					currentStageTimer = 0.f;
				}
			}
			else
			{
				uiTimerString.replace(3, std::string::npos, "0" + std::to_string(gameTimer));
			}
		}
		
		texts["UITimer"]->SetString(uiTimerString);
		uiTimer = 0.f;
	}

	if (currentStageTimer >= currentStageDuration)
	{
		texts["currentStage"]->SetActive(false);
	}

	worldMousePos = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos();
	screenMousePos = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetScreenMousePos();
	if ((screenMousePos.x > 950 && screenMousePos.y > 550) || screenMousePos.y > 600)
	{
		mouseOnUi = true;
	}
	else
	{
		mouseOnUi = false;
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && !isSelecting)
	{
		isSelecting = true;
		selectStartPos = worldMousePos;
		selectBox->SetActive(true);
		selectBox->SetPosition(selectStartPos); // 시작 위치
	}
	else if (InputMgr::GetMouseButtonUp(sf::Mouse::Left) && isSelecting)
	{
		for (SCUnit* scUnit : isSelectList)
		{
			if (scUnit != nullptr)
			{
				scUnit->SetSelect(false);
			}
		}
		isSelectList.clear();
		noUnits = true;
		isSelecting = false;
		selectBox->SetActive(false);
		// 유닛 검사
		std::list<SCUnit*> allUnit = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetAllUnitList();
		for (SCUnit* scUnit : allUnit)
		{
			if (scUnit->GetHitBox().getGlobalBounds().intersects(selectBox->GetGlobalBounds())
				|| scUnit->GetHitBox().getGlobalBounds().contains(selectBox->GetPosition()))
			{
				UItarget = scUnit;
				SetWarframeView(true);
				SetActiveUpgrade(false);
				SetActiveSell(false);
				SetActiveSellInfo(false, SCUnit::Type::Hydralisk);
				SetActiveSellInfo(false, SCUnit::Type::Ghost);
				SetActiveSellInfo(false, SCUnit::Type::Dragoon);
				noUnits = false;
				isSelectList.push_back(scUnit);
				OffUpgradeInfoView();
				OnUpgradeInfoView(scUnit->GetType());
				scUnit->SetSelect(true);
				uiStatus = UIStatus::Unit;
			}
		}

		// 건물 검사 유닛 없을때만
		if (noUnits && !mouseOnUi)
		{
			for (SCUnit* scUnit : isSelectList)
			{
				scUnit->SetSelect(false);
			}
			isSelectList.clear();
			for (const auto& pair : buildings)
			{
				Building* building = pair.second;
				if (building->GetGlobalBounds().contains(selectBox->GetPosition()))
				{
					UItarget = building;
					SetWarframeView(true);
					SetActiveUpgrade(false);
					SetActiveSell(false);
					SetActiveSellInfo(false, SCUnit::Type::Hydralisk);
					SetActiveSellInfo(false, SCUnit::Type::Ghost);
					SetActiveSellInfo(false, SCUnit::Type::Dragoon);
					OffUpgradeInfoView();
					switch (building->GetBuildingType())
					{
					case Building::BuildingType::UPGRADE:
					{
						UpgradeBuilding* Up = dynamic_cast<UpgradeBuilding*>(building);
						uiStatus = UIStatus::Upgrade;

						switch (Up->GetRace())
						{
						case Building::Races::Zerg:
							uiUnitType = SCUnit::Type::Hydralisk;
							sprites["HydraliskUpgrade"]->SetActive(true);
							Up->SetSelect(true);
							return;
							break;
						case Building::Races::Terran:
							uiUnitType = SCUnit::Type::Ghost;
							sprites["GhostUpgrade"]->SetActive(true);
							Up->SetSelect(true);
							return;
							break;
						case Building::Races::Protoss:
							uiUnitType = SCUnit::Type::Dragoon;
							sprites["DragoonUpgrade"]->SetActive(true);
							Up->SetSelect(true);
							return;
							break;
						}
						break;
					}
					case Building::BuildingType::SELL:
					{
						uiStatus = UIStatus::SellUnitSellect;
						SetActiveSell(true);
						SetWarframeView(true);
						return;
						break;
					}
					}
				}
			}
			if (!mouseOnUi) {

				UItarget = nullptr; // 아무것도 못 찍었을 때,
				uiStatus = UIStatus::NONE;
				SetActiveSell(false);
				SetActiveUpgrade(false);
				SetActiveSellInfo(false, SCUnit::Type::Hydralisk);
				SetActiveSellInfo(false, SCUnit::Type::Ghost);
				SetActiveSellInfo(false, SCUnit::Type::Dragoon);
				SetWarframeView(false);
				OffUpgradeInfoView();
			}
		}

	}

	if (isSelecting)
	{
		selectBox->SetSize(worldMousePos - selectStartPos);
	}

	switch (uiStatus)
	{
	case Interface::UIStatus::NONE:
		break;
	case Interface::UIStatus::Upgrade:
		UpdateUpgrade(dt);
		break;
	case Interface::UIStatus::SellUnitSellect:
		UpdateSellUnitSellect(dt);
		break;
	case Interface::UIStatus::SellRaritySellect:
		UpdateSellRaritySellect(dt);
		break;
	case Interface::UIStatus::Unit:
		UpdateUnit(dt);
		break;
	}

}

void Interface::UpdateUpgrade(float dt)
{
	UpgradeBuilding* building = dynamic_cast<UpgradeBuilding*>(UItarget);
	switch (building->GetRace())
	{
	case UpgradeBuilding::Races::NONE:
		break;
	case UpgradeBuilding::Races::Terran:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/TerranWarframe.png");
		warframeName.clear();
		warframeName << sf::Color::White << L"UNIT ▶UPGRADE";
		texts["UIAttackType"]->SetString(L"");
		break;
	case UpgradeBuilding::Races::Zerg:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/ZergWarframe.png");
		warframeName.clear();
		warframeName << sf::Color::White << L"UNIT ▶UPGRADE";
		texts["UIAttackType"]->SetString(L"");
		break;
	case UpgradeBuilding::Races::Protoss:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/ProtossWarframe.png");
		warframeName.clear();
		warframeName << sf::Color::White << L"UNIT ▶UPGRADE";
		texts["UIAttackType"]->SetString(L"");
		break;
	default:
		break;
	}

	switch (uiUnitType)
	{
	case SCUnit::Type::Hydralisk:
		if (sprites["HydraliskUpgrade"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
			InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "HydraliskUpgrade!!" << std::endl;
			Upgrade();
		}
		break;
	case SCUnit::Type::Dragoon:
		if (sprites["DragoonUpgrade"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
			InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "DragoonUpgrade!!" << std::endl;
			Upgrade();
		}
		break;
	case SCUnit::Type::Ghost:
		if (sprites["GhostUpgrade"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
			InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			std::cout << "GhostUpgrade!!" << std::endl;
			Upgrade();
		}
		break;
	}
	// 건물 업그레이드 상호작용
}

void Interface::UpdateSellUnitSellect(float dt)
{
	Building* building = dynamic_cast<Building*>(UItarget);
	sprites["Warframe"]->SetTexture("graphics/UI/Interface/SellWarframe.png");
	warframeName.clear();
	warframeName << sf::Color::White << L"UNIT ▶판매 & 교환";
	texts["UIAttackType"]->SetString(L"");

	// 판매 건물 상호작용
	if (sprites["GhostSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		SetActiveSell(false);
		SetActiveSellInfo(true, SCUnit::Type::Ghost);
		uiUnitType = SCUnit::Type::Ghost;
		uiStatus = UIStatus::SellRaritySellect;
	}
	else if (sprites["HydraliskSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		SetActiveSell(false);
		SetActiveSellInfo(true, SCUnit::Type::Hydralisk);
		uiUnitType = SCUnit::Type::Hydralisk;
		uiStatus = UIStatus::SellRaritySellect;
	}
	else if (sprites["DragoonSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		SetActiveSell(false);
		SetActiveSellInfo(true, SCUnit::Type::Dragoon);
		uiUnitType = SCUnit::Type::Dragoon;
		uiStatus = UIStatus::SellRaritySellect;
	}

}

void Interface::UpdateSellRaritySellect(float dt)
{
	Building* building = dynamic_cast<Building*>(UItarget);
	sprites["Warframe"]->SetTexture("graphics/UI/Interface/SellWarframe.png");
	warframeName.clear();
	warframeName << sf::Color::White << L"UNIT ▶판매 & 교환";
	texts["UIAttackType"]->SetString(L"");
	building->SetSelect(true);
	for (int i = 0; i < 5; ++i) {
		rarity[i] = 0;
	}

	switch (uiUnitType)
	{
	case SCUnit::Type::Hydralisk:
		for (auto go : dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetHydraliskList())
		{
			if ((int)go->GetRarity() > 4)
			{
				continue;
			}
			rarity[(int)go->GetRarity()]++;
		}
		SetSellUiTexture("Hydralisk", "Normal", 0);
		SetSellUiTexture("Hydralisk", "Rare", 1);
		SetSellUiTexture("Hydralisk", "Ancient", 2);
		SetSellUiTexture("Hydralisk", "Artifact", 3);
		SetSellUiTexture("Hydralisk", "Narrative", 4);
		HydraliskSellUpdate();
		break;
	case SCUnit::Type::Dragoon:
		for (auto go : dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetDragoonList())
		{
			if ((int)go->GetRarity() > 4)
			{
				continue;
			}
			rarity[(int)go->GetRarity()]++;
		}
		SetSellUiTexture("Dragoon", "Normal", 0);
		SetSellUiTexture("Dragoon", "Rare", 1);
		SetSellUiTexture("Dragoon", "Ancient", 2);
		SetSellUiTexture("Dragoon", "Artifact", 3);
		SetSellUiTexture("Dragoon", "Narrative", 4);
		DragoonSellUpdate();
		break;
	case SCUnit::Type::Ghost:
		for (auto go : dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetGhostList())
		{
			if ((int)go->GetRarity() > 4)
			{
				continue;
			}
			rarity[(int)go->GetRarity()]++;
		}
		SetSellUiTexture("Ghost", "Normal", 0);
		SetSellUiTexture("Ghost", "Rare", 1);
		SetSellUiTexture("Ghost", "Ancient", 2);
		SetSellUiTexture("Ghost", "Artifact", 3);
		SetSellUiTexture("Ghost", "Narrative", 4);
		GhostSellUpdate();
		break;
	}
}

void Interface::UpdateUnit(float dt)
{
	SCUnit* scUnit = dynamic_cast<SCUnit*>(UItarget);
	std::wstring rarityText;
	switch (scUnit->GetRarity())
	{
	case SCUnit::Rarity::NONE:
		break;
	case SCUnit::Rarity::Common:
		rarityText = L"[일반]";
		break;
	case SCUnit::Rarity::Rare:
		rarityText = L"[레어]";
		break;
	case SCUnit::Rarity::Ancient:
		rarityText = L"[고대]";
		break;
	case SCUnit::Rarity::Artifact:
		rarityText = L"[유물]";
		break;
	case SCUnit::Rarity::Saga:
		rarityText = L"[서사]";
		break;
	case SCUnit::Rarity::Legendary:
		rarityText = L"[전설]";
		break;
	case SCUnit::Rarity::Mythic:
		rarityText = L"[신화]";
		break;
	case SCUnit::Rarity::Primeval:
		rarityText = L"[태초]";
		break;
	default:
		break;
	}


	switch (scUnit->GetType())
	{
	case SCUnit::Type::NONE:
		break;
	case SCUnit::Type::Hydralisk:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/HydraliskWarframe.png");
		warframeName.clear();
		switch (scUnit->GetRarity())
		{
		case SCUnit::Rarity::Common:
			warframeName << sf::Color::White << L"히드라리스크 " << sf::Color::White << rarityText;
			break;
		case SCUnit::Rarity::Rare:
			warframeName << sf::Color::White << L"히드라리스크 " << sf::Color(0, 128, 0) << rarityText;
			break;
		case SCUnit::Rarity::Ancient:
			warframeName << sf::Color::White << L"히드라리스크 " << sf::Color(128, 0, 128) << rarityText;
			break;
		case SCUnit::Rarity::Artifact:
			warframeName << sf::Color::White << L"히드라리스크 " << sf::Color::Red << rarityText;
			break;
		case SCUnit::Rarity::Saga:
			warframeName << sf::Color::White << L"히드라리스크 " << sf::Color(0, 191, 255) << rarityText;
			break;
		case SCUnit::Rarity::Legendary:
			warframeName << sf::Color::White << L"히드라리스크 " << sf::Color::Yellow << rarityText;
			break;
		case SCUnit::Rarity::Mythic:
			warframeName << sf::Color::White << L"히드라리스크 " << sf::Color::Red << rarityText;
			break;
		case SCUnit::Rarity::Primeval:
			warframeName << sf::Color::White << L"히드라리스크 " << sf::Color(0, 191, 255) << rarityText;
			break;
		default:
			break;
		}
		texts["UIAttackType"]->SetString(L"▶ 일반형");
		break;
	case SCUnit::Type::Dragoon:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/DragoonWarframe.png");
		warframeName.clear();
		switch (scUnit->GetRarity())
		{
		case SCUnit::Rarity::Common:
			warframeName << sf::Color::White << L"드라군 " << sf::Color::White << rarityText;
			break;
		case SCUnit::Rarity::Rare:
			warframeName << sf::Color::White << L"드라군 " << sf::Color(0, 128, 0) << rarityText;
			break;
		case SCUnit::Rarity::Ancient:
			warframeName << sf::Color::White << L"드라군 " << sf::Color(128, 0, 128) << rarityText;
			break;
		case SCUnit::Rarity::Artifact:
			warframeName << sf::Color::White << L"드라군 " << sf::Color::Red << rarityText;
			break;
		case SCUnit::Rarity::Saga:
			warframeName << sf::Color::White << L"드라군 " << sf::Color(0, 191, 255) << rarityText;
			break;
		case SCUnit::Rarity::Legendary:
			warframeName << sf::Color::White << L"드라군 " << sf::Color::Yellow << rarityText;
			break;
		case SCUnit::Rarity::Mythic:
			warframeName << sf::Color::White << L"드라군 " << sf::Color::Red << rarityText;
			break;
		case SCUnit::Rarity::Primeval:
			warframeName << sf::Color::White << L"드라군 " << sf::Color(0, 191, 255) << rarityText;
			break;
		}
		texts["UIAttackType"]->SetString(L"▶ 폭발형");
		break;
	case SCUnit::Type::Ghost:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/GhostWarframe.png");
		warframeName.clear();
		switch (scUnit->GetRarity())
		{
		case SCUnit::Rarity::Common:
			warframeName << sf::Color::White << L"고스트 " << sf::Color::White << rarityText;
			break;
		case SCUnit::Rarity::Rare:
			warframeName << sf::Color::White << L"고스트 " << sf::Color(0, 128, 0) << rarityText;
			break;
		case SCUnit::Rarity::Ancient:
			warframeName << sf::Color::White << L"고스트 " << sf::Color(128, 0, 128) << rarityText;
			break;
		case SCUnit::Rarity::Artifact:
			warframeName << sf::Color::White << L"고스트 " << sf::Color::Red << rarityText;
			break;
		case SCUnit::Rarity::Saga:
			warframeName << sf::Color::White << L"고스트 " << sf::Color(0, 191, 255) << rarityText;
			break;
		case SCUnit::Rarity::Legendary:
			warframeName << sf::Color::White << L"고스트 " << sf::Color::Yellow << rarityText;
			break;
		case SCUnit::Rarity::Mythic:
			warframeName << sf::Color::White << L"고스트 " << sf::Color::Red << rarityText;
			break;
		case SCUnit::Rarity::Primeval:
			warframeName << sf::Color::White << L"고스트 " << sf::Color(0, 191, 255) << rarityText;
			break;
		}
		texts["UIAttackType"]->SetString(L"▶ 진동형");
		break;
	case SCUnit::Type::Civilian:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/CivilianWarframe.png");
		warframeName.clear();
		warframeName << sf::Color::White << L"Select Unit: 10메소";
		texts["UIAttackType"]->SetString(L"");
		break;
	default:
		break;
	}
	if (sprites["HydraliskUpgradeInfo"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		SetWeaponInfoView(true);
	}
	else
	{
		SetWeaponInfoView(false);
	}
}

void Interface::LateUpdate(float dt)
{
	UIGo::LateUpdate(dt);
}

void Interface::Draw(sf::RenderWindow& window)
{
	UIGo::Draw(window);
	if (onWarframeName)
	{
		window.draw(warframeName);
	}
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

void Interface::SetActiveSellInfo(bool active, SCUnit::Type t)
{
	switch (t)
	{
	case SCUnit::Type::Hydralisk:
		sprites["HydraliskNormal"]->SetActive(active);
		sprites["HydraliskRare"]->SetActive(active);
		sprites["HydraliskAncient"]->SetActive(active);
		sprites["HydraliskArtifact"]->SetActive(active);
		sprites["HydraliskNarrative"]->SetActive(active);
		break;
	case SCUnit::Type::Dragoon:
		sprites["DragoonNormal"]->SetActive(active);
		sprites["DragoonRare"]->SetActive(active);
		sprites["DragoonAncient"]->SetActive(active);
		sprites["DragoonArtifact"]->SetActive(active);
		sprites["DragoonNarrative"]->SetActive(active);
		break;
	case SCUnit::Type::Ghost:
		sprites["GhostNormal"]->SetActive(active);
		sprites["GhostRare"]->SetActive(active);
		sprites["GhostAncient"]->SetActive(active);
		sprites["GhostArtifact"]->SetActive(active);
		sprites["GhostNarrative"]->SetActive(active);
		break;
	}
}

void Interface::HydraliskSellUpdate()
{
	if (sprites["HydraliskNormal"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
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

	else if (sprites["HydraliskRare"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
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


	else if (sprites["HydraliskAncient"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
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

	else if (sprites["HydraliskArtifact"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
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

	else if (sprites["HydraliskNarrative"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
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

void Interface::DragoonSellUpdate()
{
	if (sprites["DragoonNormal"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Dragoon, SCUnit::Rarity::Common);
			}
		}
	}

	else if (sprites["DragoonRare"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Dragoon, SCUnit::Rarity::Rare);
			}
		}
	}


	else if (sprites["DragoonAncient"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Dragoon, SCUnit::Rarity::Ancient);
			}
		}
	}

	else if (sprites["DragoonArtifact"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Dragoon, SCUnit::Rarity::Artifact);
			}
		}
	}

	else if (sprites["DragoonNarrative"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Dragoon, SCUnit::Rarity::Saga);
			}
		}
	}
}

void Interface::GhostSellUpdate()
{
	if (sprites["GhostNormal"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Ghost, SCUnit::Rarity::Common);
			}
		}
	}

	else if (sprites["GhostRare"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Ghost, SCUnit::Rarity::Rare);
			}
		}
	}


	else if (sprites["GhostAncient"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Ghost, SCUnit::Rarity::Ancient);
			}
		}
	}

	else if (sprites["GhostArtifact"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Ghost, SCUnit::Rarity::Artifact);
			}
		}
	}

	else if (sprites["GhostNarrative"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		for (auto& data : buildings)
		{
			if (data.second->GetBuildingType() == Building::BuildingType::SELL)
			{
				SellBuilding* building = dynamic_cast<SellBuilding*>
					(data.second);
				building->Sell(SCUnit::Type::Ghost, SCUnit::Rarity::Saga);
			}
		}
	}
}

void Interface::SetSellUiTexture(const std::string& typeName, const std::string& rarityName, const int rarityIndex)
{
	std::string textureName = typeName + rarityName;
	if (rarity[rarityIndex] != 0) {
		sprites[textureName]->SetTexture("graphics/UI/Interface/" + typeName + "Sell.png");
	}
	else {
		sprites[textureName]->SetTexture("graphics/UI/Interface/" + typeName + "SellNoHave.png");
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

void Interface::SetWarframeView(bool active)
{
	sprites["Warframe"]->SetActive(active);
	onWarframeName = active;
	texts["UIAttackType"]->SetActive(active);
}

void Interface::ClearText(bool active)
{
	texts["TextClear"]->SetActive(active);
	texts["TextClear1"]->SetActive(active);
void Interface::SetWeaponInfoView(bool active)
{	
	sprites["DamageInfo"]->SetActive(active);
	texts["WeaponName"]->SetActive(active);
	texts["WeaponInterval"]->SetActive(active);
	texts["WeaponMethod"]->SetActive(active);
	texts["WeaponRange"]->SetActive(active);
	texts["WeaponDamage"]->SetActive(active);
}

void Interface::OnUpgradeInfoView(SCUnit::Type t)
{
	switch (t)
	{
	case SCUnit::Type::Hydralisk:
		sprites["HydraliskUpgradeInfo"]->SetActive(true);
		break;
	case SCUnit::Type::Dragoon:
		sprites["DragoonUpgradeInfo"]->SetActive(true);
		break;
	case SCUnit::Type::Ghost:
		sprites["GhostUpgradeInfo"]->SetActive(true);
		break;
	}
}

void Interface::OffUpgradeInfoView()
{
	sprites["HydraliskUpgradeInfo"]->SetActive(false);
	sprites["GhostUpgradeInfo"]->SetActive(false);
	sprites["DragoonUpgradeInfo"]->SetActive(false);
}
