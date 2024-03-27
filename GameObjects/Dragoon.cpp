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
	switch (rarity)
	{
	case SCUnit::Rarity::Common:
		attackRange = 5.f;
		baseDamage = 6;
		attackInterval = 1.2f;
		attackSpeed = 1.75f;
		break;
	case SCUnit::Rarity::Rare:
		attackRange = 6.f;
		baseDamage = 8;
		attackInterval = 1.2f;
		attackSpeed = 1.75f;
		break;
	case SCUnit::Rarity::Ancient:
		attackRange = 7.f;
		baseDamage = 12;
		attackInterval = 1.1f;
		attackSpeed = 2.f;
		break;
	case SCUnit::Rarity::Artifact:
		attackRange = 8.f;
		baseDamage = 16;
		attackInterval = 1.0f;
		attackSpeed = 2.f;
		break;
	case SCUnit::Rarity::Saga:
		attackRange = 9.f;
		baseDamage = 20;
		attackInterval = 1.0f;
		attackSpeed = 2.f;
		break;
	case SCUnit::Rarity::Legendary:
		attackRange = 10.f;
		baseDamage = 27;
		attackInterval = 0.8f;
		attackSpeed = 3.f;
		break;
	case SCUnit::Rarity::Mythic:
		attackRange = 11.f;
		baseDamage = 33;
		attackInterval = 0.8f;
		attackSpeed = 3.f;
		break;
	case SCUnit::Rarity::Primeval:
		attackRange = 12.f;
		baseDamage = 36;
		attackInterval = 0.7f;
		attackSpeed = 3.5f;
		break;
	}
	damage = baseDamage;
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

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && isSelect)
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
