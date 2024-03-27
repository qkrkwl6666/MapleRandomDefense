#include "pch.h"
#include "Interface.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "Crosshair.h"
#include "SceneGame.h"
#include "Building.h"
#include "UpgradeBuilding.h"
#include "SellBuilding.h"
#include "Enemy.h"
#include "Spawner.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

Interface::Interface(const std::string& name)
{

}

Interface::~Interface()
{

}

void Interface::Init()
{
	enemySpawer = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetSpawner();
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

	// 패배 메세지
	NewTextGo("TextLose", RES_MGR_FONT.Get("font/Kostar.ttf"), L"메이플 운빨 디펜스", 30, sf::Color::Blue);
	texts["TextLose"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.5f , FRAMEWORK.GetWindowSize().y * 0.4f });
	texts["TextLose"]->sortLayer = 15;
	texts["TextLose"]->SetOrigin(Origins::MC);
	texts["TextLose"]->SetActive(false);

	NewTextGo("TextLose1", RES_MGR_FONT.Get("font/Kostar.ttf"), L"패배", 30, sf::Color::Red);
	texts["TextLose1"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.5f , FRAMEWORK.GetWindowSize().y * 0.45f });
	texts["TextLose1"]->sortLayer = 15;
	texts["TextLose1"]->SetOrigin(Origins::MC);
	texts["TextLose1"]->SetActive(false);

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

	NewTextGo("UpgradeCount", RES_MGR_FONT.Get("font/Kostar.ttf"), L"0", 12, sf::Color::White);
	texts["UpgradeCount"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.49f , FRAMEWORK.GetWindowSize().y * 0.967f });
	texts["UpgradeCount"]->sortLayer = 14;
	texts["UpgradeCount"]->SetActive(false);

	NewSpriteGo("SellInfo1", "graphics/UI/Interface/SellInfo.png");
	sprites["SellInfo1"]->SetOrigin(Origins::TL);
	sprites["SellInfo1"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.68f , FRAMEWORK.GetWindowSize().y * 0.70f });
	sprites["SellInfo1"]->sortLayer = 14;
	sprites["SellInfo1"]->SetActive(false);
	sprites["SellInfo1"]->SetScale({ 1.f, 1.f });
	NewTextGo("SellInfo1", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶ 고스트 판매", 16, sf::Color::White);
	texts["SellInfo1"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.69f , FRAMEWORK.GetWindowSize().y * 0.713f });
	texts["SellInfo1"]->sortLayer = 14;
	texts["SellInfo1"]->SetActive(false);

	NewSpriteGo("SellInfo2", "graphics/UI/Interface/SellInfo.png");
	sprites["SellInfo2"]->SetOrigin(Origins::TL);
	sprites["SellInfo2"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.73f , FRAMEWORK.GetWindowSize().y * 0.70f });
	sprites["SellInfo2"]->sortLayer = 14;
	sprites["SellInfo2"]->SetActive(false);
	sprites["SellInfo2"]->SetScale({ 1.f, 1.f });
	NewTextGo("SellInfo2", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶ 히드라 판매", 16, sf::Color::White);
	texts["SellInfo2"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.74f , FRAMEWORK.GetWindowSize().y * 0.713f });
	texts["SellInfo2"]->sortLayer = 14;
	texts["SellInfo2"]->SetActive(false);


	NewSpriteGo("SellInfo3", "graphics/UI/Interface/SellInfo.png");
	sprites["SellInfo3"]->SetOrigin(Origins::TL);
	sprites["SellInfo3"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.79f , FRAMEWORK.GetWindowSize().y * 0.70f });
	sprites["SellInfo3"]->sortLayer = 14;
	sprites["SellInfo3"]->SetActive(false);
	sprites["SellInfo3"]->SetScale({ 1.f, 1.f });
	NewTextGo("SellInfo3", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶ 드라군 판매", 16, sf::Color::White);
	texts["SellInfo3"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.80f , FRAMEWORK.GetWindowSize().y * 0.713f });
	texts["SellInfo3"]->sortLayer = 14;
	texts["SellInfo3"]->SetActive(false);


	NewSpriteGo("SellRarityInfo1", "graphics/UI/Interface/SellRarityInfo.png");
	sprites["SellRarityInfo1"]->SetOrigin(Origins::TL);
	sprites["SellRarityInfo1"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.68f , FRAMEWORK.GetWindowSize().y * 0.70f });
	sprites["SellRarityInfo1"]->sortLayer = 14;
	sprites["SellRarityInfo1"]->SetActive(false);
	sprites["SellRarityInfo1"]->SetScale({ 1.f, 1.f });
	NewTextGo("SellRarityInfo1", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶ 일반 고스트", 16, sf::Color::White);
	texts["SellRarityInfo1"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.69f , FRAMEWORK.GetWindowSize().y * 0.71f });
	texts["SellRarityInfo1"]->sortLayer = 14;
	texts["SellRarityInfo1"]->SetActive(false);
	NewTextGo("SellRarityValueInfo1", RES_MGR_FONT.Get("font/Kostar.ttf"), L"3 mineral", 16, sf::Color::White);
	texts["SellRarityValueInfo1"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.695f , FRAMEWORK.GetWindowSize().y * 0.738f });
	texts["SellRarityValueInfo1"]->sortLayer = 14;
	texts["SellRarityValueInfo1"]->SetActive(false);

	NewSpriteGo("SellRarityInfo2", "graphics/UI/Interface/SellRarityInfo.png");
	sprites["SellRarityInfo2"]->SetOrigin(Origins::TL);
	sprites["SellRarityInfo2"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.73f , FRAMEWORK.GetWindowSize().y * 0.70f });
	sprites["SellRarityInfo2"]->sortLayer = 14;
	sprites["SellRarityInfo2"]->SetActive(false);
	sprites["SellRarityInfo2"]->SetScale({ 1.f, 1.f });
	NewTextGo("SellRarityInfo2", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶ 레어 고스트", 16, sf::Color::White);
	texts["SellRarityInfo2"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.74f , FRAMEWORK.GetWindowSize().y * 0.71f });
	texts["SellRarityInfo2"]->sortLayer = 14;
	texts["SellRarityInfo2"]->SetActive(false);
	NewTextGo("SellRarityValueInfo2", RES_MGR_FONT.Get("font/Kostar.ttf"), L"6 mineral", 16, sf::Color::White);
	texts["SellRarityValueInfo2"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.745f , FRAMEWORK.GetWindowSize().y * 0.738f });
	texts["SellRarityValueInfo2"]->sortLayer = 14;
	texts["SellRarityValueInfo2"]->SetActive(false);

	NewSpriteGo("SellRarityInfo3", "graphics/UI/Interface/SellRarityInfo.png");
	sprites["SellRarityInfo3"]->SetOrigin(Origins::TL);
	sprites["SellRarityInfo3"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.79f , FRAMEWORK.GetWindowSize().y * 0.70f });
	sprites["SellRarityInfo3"]->sortLayer = 14;
	sprites["SellRarityInfo3"]->SetActive(false);
	sprites["SellRarityInfo3"]->SetScale({ 1.f, 1.f });
	NewTextGo("SellRarityInfo3", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶ 고대 고스트", 16, sf::Color::White);
	texts["SellRarityInfo3"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.80f , FRAMEWORK.GetWindowSize().y * 0.71f });
	texts["SellRarityInfo3"]->sortLayer = 14;
	texts["SellRarityInfo3"]->SetActive(false);
	NewTextGo("SellRarityValueInfo3", RES_MGR_FONT.Get("font/Kostar.ttf"), L"9 mineral", 16, sf::Color::White);
	texts["SellRarityValueInfo3"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.805f , FRAMEWORK.GetWindowSize().y * 0.738f });
	texts["SellRarityValueInfo3"]->sortLayer = 14;
	texts["SellRarityValueInfo3"]->SetActive(false);

	NewSpriteGo("SellRarityInfo4", "graphics/UI/Interface/SellRarityInfo.png");
	sprites["SellRarityInfo4"]->SetOrigin(Origins::TL);
	sprites["SellRarityInfo4"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.68f , FRAMEWORK.GetWindowSize().y * 0.77f });
	sprites["SellRarityInfo4"]->sortLayer = 14;
	sprites["SellRarityInfo4"]->SetActive(false);
	sprites["SellRarityInfo4"]->SetScale({ 1.f, 1.f });
	NewTextGo("SellRarityInfo4", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶ 유물 고스트", 16, sf::Color::White);
	texts["SellRarityInfo4"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.69f , FRAMEWORK.GetWindowSize().y * 0.78f });
	texts["SellRarityInfo4"]->sortLayer = 14;
	texts["SellRarityInfo4"]->SetActive(false);
	NewTextGo("SellRarityValueInfo4", RES_MGR_FONT.Get("font/Kostar.ttf"), L"16 mineral", 16, sf::Color::White);
	texts["SellRarityValueInfo4"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.695f , FRAMEWORK.GetWindowSize().y * 0.808f });
	texts["SellRarityValueInfo4"]->sortLayer = 14;
	texts["SellRarityValueInfo4"]->SetActive(false);

	NewSpriteGo("SellRarityInfo5", "graphics/UI/Interface/SellRarityInfo.png");
	sprites["SellRarityInfo5"]->SetOrigin(Origins::TL);
	sprites["SellRarityInfo5"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.73f , FRAMEWORK.GetWindowSize().y * 0.77f });
	sprites["SellRarityInfo5"]->sortLayer = 14;
	sprites["SellRarityInfo5"]->SetActive(false);
	sprites["SellRarityInfo5"]->SetScale({ 1.f, 1.f });
	NewTextGo("SellRarityInfo5", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶ 서사 고스트", 16, sf::Color::White);
	texts["SellRarityInfo5"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.74f , FRAMEWORK.GetWindowSize().y * 0.78f });
	texts["SellRarityInfo5"]->sortLayer = 14;
	texts["SellRarityInfo5"]->SetActive(false);
	NewTextGo("SellRarityValueInfo5", RES_MGR_FONT.Get("font/Kostar.ttf"), L"30 mineral", 16, sf::Color::White);
	texts["SellRarityValueInfo5"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.745f , FRAMEWORK.GetWindowSize().y * 0.808f });
	texts["SellRarityValueInfo5"]->sortLayer = 14;
	texts["SellRarityValueInfo5"]->SetActive(false);

	NewSpriteGo("UpgradeInfo", "graphics/UI/Interface/UpgradeInfo.png");
	sprites["UpgradeInfo"]->SetOrigin(Origins::TL);
	sprites["UpgradeInfo"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.68f , FRAMEWORK.GetWindowSize().y * 0.645f });
	sprites["UpgradeInfo"]->sortLayer = 14;
	sprites["UpgradeInfo"]->SetActive(false);
	sprites["UpgradeInfo"]->SetScale({ 1.f, 1.f });
	NewTextGo("UpgradeInfo", RES_MGR_FONT.Get("font/Kostar.ttf"), L"▶ Upgrade Hydralisk Weapons", 18, sf::Color::Yellow);
	texts["UpgradeInfo"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.69f , FRAMEWORK.GetWindowSize().y * 0.65f });
	texts["UpgradeInfo"]->sortLayer = 14;
	texts["UpgradeInfo"]->SetActive(false);
	NewTextGo("UpgradeInfo2", RES_MGR_FONT.Get("font/Kostar.ttf"), L"Next Level :", 18, sf::Color::White);
	texts["UpgradeInfo2"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.69f , FRAMEWORK.GetWindowSize().y * 0.678f });
	texts["UpgradeInfo2"]->sortLayer = 14;
	texts["UpgradeInfo2"]->SetActive(false);
	NewSpriteGo("UpgradeInfoMineral", "graphics/UI/Interface/minerals.png");
	sprites["UpgradeInfoMineral"]->SetOrigin(Origins::TL);
	sprites["UpgradeInfoMineral"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.69f , FRAMEWORK.GetWindowSize().y * 0.71f });
	sprites["UpgradeInfoMineral"]->sortLayer = 14;
	sprites["UpgradeInfoMineral"]->SetScale({ 0.7f, 0.7f });
	sprites["UpgradeInfoMineral"]->SetActive(false);
	NewTextGo("UpgradeInfo3", RES_MGR_FONT.Get("font/Kostar.ttf"), L"11", 18, sf::Color::White);
	texts["UpgradeInfo3"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.71f , FRAMEWORK.GetWindowSize().y * 0.71f });
	texts["UpgradeInfo3"]->sortLayer = 14;
	texts["UpgradeInfo3"]->SetActive(false);

	NewTextGo("EnemyHP", RES_MGR_FONT.Get("font/Kostar.ttf"), L"34/35", 17, sf::Color::Green);
	texts["EnemyHP"]->SetPosition({ FRAMEWORK.GetWindowSize().x *
	0.333f , FRAMEWORK.GetWindowSize().y * 0.948f });
	texts["EnemyHP"]->sortLayer = 14;
	texts["EnemyHP"]->SetActive(false);

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
	std::cout << (int)uiStatus << std::endl;
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

			std::list<Enemy*>* enemyListPtr = enemySpawer->GetEnemys();
			if (enemyListPtr) {
				std::list<Enemy*>& enemyList = *enemyListPtr;
				for (Enemy* enemy : enemyList)
				{
					if (enemy->GetGlobalBounds().contains(selectBox->GetPosition()))
					{
						UItarget = enemy;
						SetWarframeView(true);
						SetActiveUpgrade(false);
						SetActiveSell(false);
						SetActiveSellInfo(false, SCUnit::Type::Hydralisk);
						SetActiveSellInfo(false, SCUnit::Type::Ghost);
						SetActiveSellInfo(false, SCUnit::Type::Dragoon);
						OffUpgradeInfoView();
						uiStatus = UIStatus::Enemy;
						return;
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
	case Interface::UIStatus::Enemy:
		UpdateEnemy(dt);
		break;
	}

}

void Interface::UpdateUpgrade(float dt)
{
	UpgradeBuilding* building = dynamic_cast<UpgradeBuilding*>(UItarget);

	if (sprites["HydraliskUpgrade"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		sprites["UpgradeInfo"]->SetActive(true);
		texts["UpgradeInfo"]->SetActive(true);
		texts["UpgradeInfo2"]->SetActive(true);
		sprites["UpgradeInfoMineral"]->SetActive(true);
		texts["UpgradeInfo3"]->SetActive(true);
	}
	else
	{
		sprites["UpgradeInfo"]->SetActive(false);
		texts["UpgradeInfo"]->SetActive(false);
		texts["UpgradeInfo2"]->SetActive(false);
		sprites["UpgradeInfoMineral"]->SetActive(false);
		texts["UpgradeInfo3"]->SetActive(false);
	}

	switch (building->GetRace())
	{
	case UpgradeBuilding::Races::NONE:
		break;
	case UpgradeBuilding::Races::Terran:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/TerranWarframe.png");
		warframeName.clear();
		warframeName << sf::Color::White << L"UNIT ▶UPGRADE";
		texts["UIAttackType"]->SetString(L"");
		texts["UpgradeInfo"]->SetString(L"Upgrade Ghost Weapons");
		texts["UpgradeInfo2"]->SetString(L"Next Level: " + std::to_wstring(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetGhostUpgrade() + 1));
		texts["UpgradeInfo3"]->SetString(std::to_wstring(12 + (dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetGhostUpgrade()) * 3));
		break;
	case UpgradeBuilding::Races::Zerg:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/ZergWarframe.png");
		warframeName.clear();
		warframeName << sf::Color::White << L"UNIT ▶UPGRADE";
		texts["UIAttackType"]->SetString(L"");
		texts["UpgradeInfo"]->SetString(L"Upgrade Hydralisk Weapons");
		texts["UpgradeInfo2"]->SetString(L"Next Level: " + std::to_wstring(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetHydraliskUpgrade() + 1));
		texts["UpgradeInfo3"]->SetString(std::to_wstring(10 + (dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetHydraliskUpgrade()) * 2));
		break;
	case UpgradeBuilding::Races::Protoss:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/ProtossWarframe.png");
		warframeName.clear();
		warframeName << sf::Color::White << L"UNIT ▶UPGRADE";
		texts["UIAttackType"]->SetString(L"");
		texts["UpgradeInfo"]->SetString(L"Upgrade Dragoon Weapons");
		texts["UpgradeInfo2"]->SetString(L"Next Level: " + std::to_wstring(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetDragoonUpgrade() + 1));
		texts["UpgradeInfo3"]->SetString(std::to_wstring(12 + (dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetDragoonUpgrade()) * 3));
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
		return;
	}
	else if (sprites["HydraliskSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		SetActiveSell(false);
		SetActiveSellInfo(true, SCUnit::Type::Hydralisk);
		uiUnitType = SCUnit::Type::Hydralisk;
		uiStatus = UIStatus::SellRaritySellect;
		return;
	}
	else if (sprites["DragoonSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()) &&
		InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		SetActiveSell(false);
		SetActiveSellInfo(true, SCUnit::Type::Dragoon);
		uiUnitType = SCUnit::Type::Dragoon;
		uiStatus = UIStatus::SellRaritySellect;
		return;
	}

	if (sprites["GhostSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		sprites["SellInfo1"]->SetActive(true);
		texts["SellInfo1"]->SetActive(true);
	}
	else
	{
		sprites["SellInfo1"]->SetActive(false);
		texts["SellInfo1"]->SetActive(false);
	}

	if (sprites["HydraliskSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		sprites["SellInfo2"]->SetActive(true);
		texts["SellInfo2"]->SetActive(true);
	}
	else
	{
		sprites["SellInfo2"]->SetActive(false);
		texts["SellInfo2"]->SetActive(false);
	}

	if (sprites["DragoonSell"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		sprites["SellInfo3"]->SetActive(true);
		texts["SellInfo3"]->SetActive(true);
	}
	else
	{
		sprites["SellInfo3"]->SetActive(false);
		texts["SellInfo3"]->SetActive(false);
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
		texts["SellRarityInfo1"]->SetString(L"▶ 일반 히드라");
		texts["SellRarityInfo2"]->SetString(L"▶ 레어 히드라");
		texts["SellRarityInfo3"]->SetString(L"▶ 고대 히드라");
		texts["SellRarityInfo4"]->SetString(L"▶ 유물 히드라");
		texts["SellRarityInfo5"]->SetString(L"▶ 서사 히드라");
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
		texts["SellRarityInfo1"]->SetString(L"▶ 일반 드라군");
		texts["SellRarityInfo2"]->SetString(L"▶ 레어 드라군");
		texts["SellRarityInfo3"]->SetString(L"▶ 고대 드라군");
		texts["SellRarityInfo4"]->SetString(L"▶ 유물 드라군");
		texts["SellRarityInfo5"]->SetString(L"▶ 서사 드라군");
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
		texts["SellRarityInfo1"]->SetString(L"▶ 일반 고스트");
		texts["SellRarityInfo2"]->SetString(L"▶ 레어 고스트");
		texts["SellRarityInfo3"]->SetString(L"▶ 고대 고스트");
		texts["SellRarityInfo4"]->SetString(L"▶ 유물 고스트");
		texts["SellRarityInfo5"]->SetString(L"▶ 서사 고스트");
		SetSellUiTexture("Ghost", "Normal", 0);
		SetSellUiTexture("Ghost", "Rare", 1);
		SetSellUiTexture("Ghost", "Ancient", 2);
		SetSellUiTexture("Ghost", "Artifact", 3);
		SetSellUiTexture("Ghost", "Narrative", 4);
		GhostSellUpdate();
		break;
	}

	if (sprites["HydraliskNormal"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		sprites["SellRarityInfo1"]->SetActive(true);
		texts["SellRarityInfo1"]->SetActive(true);
		texts["SellRarityValueInfo1"]->SetActive(true);
	}
	else
	{
		sprites["SellRarityInfo1"]->SetActive(false);
		texts["SellRarityInfo1"]->SetActive(false);
		texts["SellRarityValueInfo1"]->SetActive(false);
	}

	if (sprites["HydraliskRare"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		sprites["SellRarityInfo2"]->SetActive(true);
		texts["SellRarityInfo2"]->SetActive(true);
		texts["SellRarityValueInfo2"]->SetActive(true);
	}
	else
	{
		sprites["SellRarityInfo2"]->SetActive(false);
		texts["SellRarityInfo2"]->SetActive(false);
		texts["SellRarityValueInfo2"]->SetActive(false);
	}

	if (sprites["HydraliskAncient"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		sprites["SellRarityInfo3"]->SetActive(true);
		texts["SellRarityInfo3"]->SetActive(true);
		texts["SellRarityValueInfo3"]->SetActive(true);
	}
	else
	{
		sprites["SellRarityInfo3"]->SetActive(false);
		texts["SellRarityInfo3"]->SetActive(false);
		texts["SellRarityValueInfo3"]->SetActive(false);
	}

	if (sprites["HydraliskArtifact"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		sprites["SellRarityInfo4"]->SetActive(true);
		texts["SellRarityInfo4"]->SetActive(true);
		texts["SellRarityValueInfo4"]->SetActive(true);
	}
	else
	{
		sprites["SellRarityInfo4"]->SetActive(false);
		texts["SellRarityInfo4"]->SetActive(false);
		texts["SellRarityValueInfo4"]->SetActive(false);
	}

	if (sprites["HydraliskNarrative"]->GetGlobalBounds().contains(FRAMEWORK.GetMouse()->GetPosition()))
	{
		sprites["SellRarityInfo5"]->SetActive(true);
		texts["SellRarityInfo5"]->SetActive(true);
		texts["SellRarityValueInfo5"]->SetActive(true);
	}
	else
	{
		sprites["SellRarityInfo5"]->SetActive(false);
		texts["SellRarityInfo5"]->SetActive(false);
		texts["SellRarityValueInfo5"]->SetActive(false);
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

	texts["UpgradeCount"]->SetString(std::to_wstring(scUnit->GetUpgrade()));

	std::wstringstream ss;
	ss << std::fixed << std::setprecision(2) << scUnit->GetAttackSpeed();
	std::wstring result = ss.str();
	texts["WeaponInterval"]->SetString(L"공격속도 : x" + result);
	texts["WeaponMethod"]->SetString(L"공격방식 : 단일개체");
	texts["WeaponRange"]->SetString(L"사거리 : " + std::to_wstring(scUnit->GetRange()));
	texts["WeaponDamage"]->SetString(L"Damage : " + std::to_wstring(scUnit->GetDamage()));

	switch (scUnit->GetType())
	{
	case SCUnit::Type::NONE:
		break;
	case SCUnit::Type::Hydralisk:
	{
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/HydraliskWarframe.png");
		warframeName.clear();
	}
	if (onDamageInfo)
	{
		warframeName << sf::Color::White << L"히드라";
	}
	else
	{
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
	}
	texts["UIAttackType"]->SetString(L"▶ 일반형");
	texts["WeaponName"]->SetString(L"Needle Spines");
	break;

	case SCUnit::Type::Dragoon:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/DragoonWarframe.png");
		warframeName.clear();
		if (onDamageInfo)
		{
			warframeName << sf::Color::White << L"드라군";
		}
		else
		{
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
		}
		texts["UIAttackType"]->SetString(L"▶ 폭발형");
		texts["WeaponName"]->SetString(L"Cast Optical Flare");
		texts["UIAttackType"]->sortLayer = 11;
		break;
	case SCUnit::Type::Ghost:
		sprites["Warframe"]->SetTexture("graphics/UI/Interface/GhostWarframe.png");
		warframeName.clear();
		if (onDamageInfo)
		{
			warframeName << sf::Color::White << L"고스트";
		}
		else
		{
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
		}
		texts["UIAttackType"]->SetString(L"▶ 진동형");
		texts["WeaponName"]->SetString(L"C-10 Canister Rifle");
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
		onDamageInfo = true;
	}
	else
	{
		SetWeaponInfoView(false);
		onDamageInfo = false;
	}
}

void Interface::UpdateEnemy(float dt)
{
	Enemy* enemy = dynamic_cast<Enemy*>(UItarget);//TO-DO 체력바 active true 하기 , 숫자 바꾸기, 다른상황일떄 끄기
	sprites["Warframe"]->SetTexture("graphics/UI/Interface/HydraliskWarframe.png");
	warframeName.clear();
	warframeName << sf::Color::White << L"Select Unit: 10메소";
	texts["UIAttackType"]->SetString(L"");
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

	sprites["UpgradeInfo"]->SetActive(false);
	texts["UpgradeInfo"]->SetActive(false);
	texts["UpgradeInfo2"]->SetActive(false);
	sprites["UpgradeInfoMineral"]->SetActive(false);
	texts["UpgradeInfo3"]->SetActive(false);

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
	sprites["SellInfo1"]->SetActive(false);
	texts["SellInfo1"]->SetActive(false);
	sprites["SellInfo2"]->SetActive(false);
	texts["SellInfo2"]->SetActive(false);
	sprites["SellInfo3"]->SetActive(false);
	texts["SellInfo3"]->SetActive(false);

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
	sprites["SellRarityInfo1"]->SetActive(false);
	texts["SellRarityInfo1"]->SetActive(false);
	texts["SellRarityValueInfo1"]->SetActive(false);
	sprites["SellRarityInfo2"]->SetActive(false);
	texts["SellRarityInfo2"]->SetActive(false);
	texts["SellRarityValueInfo2"]->SetActive(false);
	sprites["SellRarityInfo3"]->SetActive(false);
	texts["SellRarityInfo3"]->SetActive(false);
	texts["SellRarityValueInfo3"]->SetActive(false);
	sprites["SellRarityInfo4"]->SetActive(false);
	texts["SellRarityInfo4"]->SetActive(false);
	texts["SellRarityValueInfo4"]->SetActive(false);
	sprites["SellRarityInfo5"]->SetActive(false);
	texts["SellRarityInfo5"]->SetActive(false);
	texts["SellRarityValueInfo5"]->SetActive(false);
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
		std::string SellRarityInfo = "SellRarityInfo" + std::to_string(rarityIndex + 1);
		texts[SellRarityInfo]->SetString(L"▶ 유닛이 없습니다");
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
}

void Interface::LoseText(bool active)
{
	texts["TextLose"]->SetActive(active);
	texts["TextLose1"]->SetActive(active);
}

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
		texts["UpgradeCount"]->SetActive(true);
		break;
	case SCUnit::Type::Dragoon:
		sprites["DragoonUpgradeInfo"]->SetActive(true);
		texts["UpgradeCount"]->SetActive(true);
		break;
	case SCUnit::Type::Ghost:
		sprites["GhostUpgradeInfo"]->SetActive(true);
		texts["UpgradeCount"]->SetActive(true);
		break;
	}
}

void Interface::OffUpgradeInfoView()
{
	sprites["HydraliskUpgradeInfo"]->SetActive(false);
	sprites["GhostUpgradeInfo"]->SetActive(false);
	sprites["DragoonUpgradeInfo"]->SetActive(false);
	texts["UpgradeCount"]->SetActive(false);
}