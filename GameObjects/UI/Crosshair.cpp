#include "pch.h"
#include "Crosshair.h"
#include "SCUnit.h"
#include "Building.h"
#include "SceneGame.h"
#include "Spawner.h"
#include "Enemy.h"
#include "Interface.h"


Crosshair::Crosshair(const std::string& name)
{
	sortLayer = 20;
	textureId = "graphics/UI/cursor.png";
	SetTexture(textureId);
	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::TL);
}

void Crosshair::Init()
{
	SpriteAnimatorGo::Init();
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/MovingCursor.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/EnemyMovingCursor.csv"));
}

void Crosshair::Release()
{
	SpriteAnimatorGo::Release();
}

void Crosshair::Reset()
{
	SpriteAnimatorGo::Reset();
}

void Crosshair::Update(float dt)
{
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToUi((sf::Vector2i)InputMgr::GetMousePos());
	SetPosition(mouseWorldPos);
	animator->Update(dt);
	std::list<SCUnit*> allUnit = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetAllUnitList();
	for (SCUnit* scUnit : allUnit)
	{
		if (scUnit->GetHitBox().getGlobalBounds().contains(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos()))
		{
			isCursorsUnitCollision = true;
			break;
		}
		isCursorsUnitCollision = false;
	}

	std::unordered_map<std::string, Building*>& allBuilding = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetBuildings();
	for (const auto& pair : allBuilding)
	{
		Building* buildingPtr = pair.second;
		if (buildingPtr->GetGlobalBounds().contains(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos()))
		{
			isCursorsBuildingCollision = true;
			break;
		}
		isCursorsBuildingCollision = false;
	}

	std::list<Enemy*>* enemyListPtr = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetSpawner()->GetEnemys();
	if (enemyListPtr) {
		std::list<Enemy*>& enemyList = *enemyListPtr;
		for (Enemy* enemy : enemyList)
		{
			if (enemy->GetGlobalBounds().contains(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos()))
			{
				isCursorsEnemyCollision = true;
				break;
			}
			isCursorsEnemyCollision = false;
		}
	}
	if ((isCursorsUnitCollision || isCursorsBuildingCollision) && !isCursorsMoving)
	{
		animator->Play("MovingCursor", true);
		isCursorsMoving = true;
		SetOrigin(Origins::MC);
	}
	else if (isCursorsEnemyCollision && !isCursorsMoving)
	{
		animator->Play("EnemyMovingCursor", true);
		isCursorsMoving = true;
		SetOrigin(Origins::MC);
	}
	else if (!isCursorsUnitCollision && !isCursorsBuildingCollision && !isCursorsEnemyCollision)
	{
		SetOrigin(Origins::TL);
		SetTexture(textureId);
		isCursorsMoving = false;
	}

	if (((SCENE_MGR.GetCurrentScene()) == SCENE_MGR.GetScene(SceneIds::SceneTitle)) || 
		dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetInterface()->GetMouseOnUi())
	{
		SetOrigin(Origins::TL);
		SetTexture(textureId);
		isCursorsMoving = false;
	}
}

void Crosshair::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

