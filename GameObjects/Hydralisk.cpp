#include "pch.h"
#include "Hydralisk.h"
#include "Crosshair.h"
#include "SceneGame.h"
#include "Projectile.h"

Hydralisk::Hydralisk(const std::string& name, SCUnit::Rarity r)
	: SCUnit(name, "Hydralisk")
{
	rarity = r;
	attackRange = 6.f;
	attackInterval = 1.f;
}

Hydralisk::~Hydralisk()
{

}

void Hydralisk::Init()
{
	SCUnit::Init();

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

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && isSelect && currentStatus != Status::ATTACK)
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
