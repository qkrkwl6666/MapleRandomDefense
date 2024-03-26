#include "pch.h"
#include "Dragoon.h"
#include "Crosshair.h"
#include "SceneGame.h"
#include "Enemy.h"

Dragoon::Dragoon(const std::string& name, SCUnit::Rarity r)
	: SCUnit(name, "Dragoon")
{
	rarity = r;
}

Dragoon::~Dragoon()
{
}

void Dragoon::Init()
{
	SCUnit::Init();

	SetTexture("graphics/Dragoon.png");
	hitBox.setSize({ 30.f,30.f });
	hitBox.setOrigin(hitBox.getSize() / 2.f);
	GetSprite()->setTextureRect({ 0, 0, 65, 65 });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Dragoon.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/DragoonIdle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/DragoonAttack.csv"));

	isSelectSprite->SetScale({ 2.f , 2.f });

	SetScale({ 1.f , 1.f });
	SetOrigin(Origins::MC);

	type = SCUnit::Type::Dragoon;
}

void Dragoon::Reset()
{
	SCUnit::Reset();
}

void Dragoon::Update(float dt)
{
	SCUnit::Update(dt);


	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && isSelect && currentStatus != Status::ATTACK)
	{
		Astar(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos());
	}
}

void Dragoon::LateUpdate(float dt)
{
	SCUnit::LateUpdate(dt);
}

void Dragoon::Draw(sf::RenderWindow& window)
{
	SCUnit::Draw(window);
}
