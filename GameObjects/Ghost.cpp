#include "pch.h"
#include "Ghost.h"
#include "Crosshair.h"
#include "SceneGame.h"
#include "Projectile.h"
#include "Enemy.h"

Ghost::Ghost(const std::string& name, SCUnit::Rarity r)
	: SCUnit(name, "Ghost")
{
	rarity = r;

}

Ghost::~Ghost()
{
}

void Ghost::Init()
{
	SCUnit::Init();
	switch (rarity)
	{
	case SCUnit::Rarity::Common:
		attackRange = 5.f;
		baseDamage = 8;
		attackInterval = 1.0f;
		attackSpeed = 2.f;
		break;
	case SCUnit::Rarity::Rare:
		attackRange = 6.f;
		baseDamage = 10;
		attackInterval = 1.0f;
		attackSpeed = 2.f;
		break;
	case SCUnit::Rarity::Ancient:
		attackRange = 7.f;
		baseDamage = 15;
		attackInterval = 0.9f;
		attackSpeed = 2.25f;

		break;
	case SCUnit::Rarity::Artifact:
		attackRange = 8.f;
		baseDamage = 20;
		attackInterval = 0.9f;
		attackSpeed = 2.25f;

		break;
	case SCUnit::Rarity::Saga:
		attackRange = 9.f;
		baseDamage = 24;
		attackInterval = 0.8f;
		attackSpeed = 2.5f;
		break;
	case SCUnit::Rarity::Legendary:
		attackRange = 10.f;
		baseDamage = 29;
		attackInterval = 0.7f;
		attackSpeed = 3.f;
		break;
	case SCUnit::Rarity::Mythic:
		attackRange = 11.f;
		baseDamage = 38;
		attackInterval = 0.7f;
		attackSpeed = 3.f;
		break;
	case SCUnit::Rarity::Primeval:
		attackRange = 12.f;
		baseDamage = 40;
		attackInterval = 0.6f;
		attackSpeed = 4.f;
		break;
	}
	damage = baseDamage;
	SetTexture("graphics/Ghost.png");

	GetSprite()->setTextureRect({ 0, 114, 42, 38 });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Ghost.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/GhostAttack.csv"));

	SetScale({ 1.f , 1.f });
	SetOrigin(Origins::MC);

	type = SCUnit::Type::Ghost;

	projectile->SetTexture("graphics/GhostProjectile.png");
	projectile->GetSprite()->setTextureRect({ 0, 0,	38,	37});
	projectile->SetOrigin(Origins::MC);
	projectile->SetScale({ 1.f , 1.f });
	projectile->GetAnimator()->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/GhostProjectile.csv"));

	projectile->GetAnimator()->AddEvent("GhostProjectile", 1, [this]()
		{
			this->projectile->SetPosition(this->GetTarget()->GetPosition());
		});
}

void Ghost::Reset()
{
	SCUnit::Reset();
}

void Ghost::Update(float dt)
{
	SCUnit::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && isSelect)
	{
		Astar(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos());
	}

	//if (projectile->GetActive() && target != nullptr)
	//{
	//	projectile->SetPosition(target->GetPosition());
	//}
}

void Ghost::LateUpdate(float dt)
{
	SCUnit::LateUpdate(dt);
}

void Ghost::Draw(sf::RenderWindow& window)
{
	SCUnit::Draw(window);
}
