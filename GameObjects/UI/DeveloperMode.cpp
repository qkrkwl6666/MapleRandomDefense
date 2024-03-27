#include "pch.h"
#include "DeveloperMode.h"
#include "SceneGame.h"
#include "Spawner.h"

DeveloperMode::DeveloperMode(const std::string& name)
{
}

DeveloperMode::~DeveloperMode()
{
}

void DeveloperMode::Init()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));

	NewTextGo("TextFPS", RES_MGR_FONT.Get("font/Kostar.ttf"), L"", 20, sf::Color::White);
	texts["TextFPS"]->SetPosition({ 0.f , 0.f });
	texts["TextFPS"]->sortLayer = 15;
	texts["TextFPS"]->SetString("FPS : ");
	texts["TextFPS"]->SetCharacterSize(30);
	texts["TextFPS"]->SetOrigin(Origins::TL);

	NewTextGo("TextEnemysCount", RES_MGR_FONT.Get("font/Kostar.ttf"), L"", 20, sf::Color::White);
	texts["TextEnemysCount"]->SetPosition({ 0.f , FRAMEWORK.GetWindowSize().y * 0.05f });
	texts["TextEnemysCount"]->sortLayer = 15;
	texts["TextEnemysCount"]->SetString("���� �� : ");
	texts["TextEnemysCount"]->SetCharacterSize(30);
	texts["TextEnemysCount"]->SetOrigin(Origins::TL);

	enemyList = sceneGame->GetEnemyList();
	
	UiInit();
	ObjectsSort();
}

void DeveloperMode::Release()
{
	UIGo::Release();
}

void DeveloperMode::Reset()
{
	UIGo::Reset();
}

void DeveloperMode::Update(float dt)
{
	UIGo::Update(dt);
	texts["TextFPS"]->SetString("FPS : " + std::to_string(FRAMEWORK.GetFrame()));
	texts["TextEnemysCount"]->SetString(L"���� �� : " + Utils::CP949ToWString(std::to_string(enemyList->size())));

	// ��ġƮ
	if (InputMgr::GetKeyDown(sf::Keyboard::F8))
	{
		sceneGame->SetMineral(sceneGame->GetMineral() + 100);
	}
	// �� ALL Dead
	if (InputMgr::GetKeyDown(sf::Keyboard::F9))
	{
		sceneGame->GetSpawner()->AllRemove();
	}
	// �ӵ� 10��
	if (InputMgr::GetKeyDown(sf::Keyboard::F10))
	{
		FRAMEWORK.SetTimeScale(10.f);
	}
}

void DeveloperMode::LateUpdate(float dt)
{
	UIGo::LateUpdate(dt);
}