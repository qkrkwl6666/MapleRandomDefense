#include "pch.h"
#include "Hydralisk.h"
#include "Crosshair.h"
#include "SceneGame.h"
#include "Projectile.h"

Hydralisk::Hydralisk(const std::string& name, SCUnit::Rarity r)
	: SCUnit(name, "Hydralisk")
{
	rarity = r;
}

Hydralisk::~Hydralisk()
{

}

void Hydralisk::Init()
{
	SCUnit::Init();
	switch (rarity)
	{
	case SCUnit::Rarity::Common:
		attackRange = 5.f;
		baseDamage = 3;
		attackInterval = 1.0f;
		attackSpeed = 2.f;
		break;
	case SCUnit::Rarity::Rare:
		attackRange = 6.f;
		baseDamage = 4;
		attackInterval = 1.0f;
		attackSpeed = 2.f;
		break;
	case SCUnit::Rarity::Ancient:
		attackRange = 7.f;
		baseDamage = 6;
		attackInterval = 0.9f;
		attackSpeed = 2.25f;
		break;
	case SCUnit::Rarity::Artifact:
		attackRange = 8.f;
		baseDamage = 8;
		attackInterval = 0.9f;
		attackSpeed = 2.25f;
		break;
	case SCUnit::Rarity::Saga:
		attackRange = 9.f;
		baseDamage = 10;
		attackInterval = 0.8f;
		attackSpeed = 2.5f;
		break;
	case SCUnit::Rarity::Legendary:
		attackRange = 10.f;
		baseDamage = 14;
		attackInterval = 0.7f;
		attackSpeed = 3.f;
		break;
	case SCUnit::Rarity::Mythic:
		attackRange = 11.f;
		baseDamage = 17;
		attackInterval = 0.7f;
		attackSpeed = 3.f;
		break;
	case SCUnit::Rarity::Primeval:
		attackRange = 12.f;
		baseDamage = 20;
		attackInterval = 0.6f;
		attackSpeed = 4.f;
		break;
	}
	damage = baseDamage;
	SetTexture("graphics/Hydralisk.png");

	GetSprite()->setTextureRect({ 0, 174, 45, 58});

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Hydralisk.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/HydraliskAttack.csv"));

	SetScale({ 1.f , 1.f });
	SetOrigin(Origins::MC);

	type = SCUnit::Type::Hydralisk;

	projectile->SetTexture("graphics/HydraliskProjectile.png");
	projectile->GetSprite()->setTextureRect({ 0, 0,	89,	125});
	projectile->SetOrigin(Origins::MC);
	projectile->SetScale({ 1.f , 1.f });
	projectile->GetAnimator()->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/HydraliskProjectile.csv"));
}

void Hydralisk::Reset()
{
	SCUnit::Reset();
}

void Hydralisk::Update(float dt)
{
	SCUnit::Update(dt);

	if (projectile->GetActive() && !GetFlipX())
	{
		projectile->SetPosition({GetPosition().x + 19.f, GetPosition().y});
	}
	else
	{
		projectile->SetPosition({ GetPosition().x - 19.f, GetPosition().y });
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && isSelect)
	{
		Astar(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos());
	}
}

void Hydralisk::LateUpdate(float dt)
{
	SCUnit::LateUpdate(dt);
}

void Hydralisk::Draw(sf::RenderWindow& window)
{
	SCUnit::Draw(window);
}
