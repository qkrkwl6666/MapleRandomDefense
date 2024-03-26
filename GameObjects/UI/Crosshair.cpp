#include "pch.h"
#include "Crosshair.h"
#include "SCUnit.h"
#include "SceneGame.h"


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
	//animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/MovingCursor.csv"));
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
			isCursorsCollision = true;
			break;
		}
		isCursorsCollision = false;
	}

	//if (isCursorsCollision && !isCursorsMoving) 
	//{
	//	animator->Play("MovingCursor", true);
	//	isCursorsMoving = true;
	//	SetOrigin(Origins::MC);
	//}
	//else if (!isCursorsCollision)
	//{
	//	SetOrigin(Origins::TL);
	//	SetTexture(textureId);
	//	isCursorsMoving = false;
	//}
}

void Crosshair::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

