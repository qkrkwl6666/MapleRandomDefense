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

	if (projectile->GetActive())
	{
		projectile->SetPosition({GetPosition().x + 19.f, GetPosition().y});
	}

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && isSelect)
	{
		Astar(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos());
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		currentAngle = Angle::TOP;
		SetStatus(Status::ATTACK);

	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		currentAngle = Angle::TOP15;

	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		currentAngle = Angle::TOP30;

	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
	{
		currentAngle = Angle::TOP60;

	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num5))
	{
		currentAngle = Angle::RIGHT;
		SetStatus(Status::IDLE);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num6))
	{
		currentAngle = Angle::BOTTOM60;

	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num7))
	{
		currentAngle = Angle::BOTTOM30;

	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num8))
	{
		currentAngle = Angle::BOTTOM15;

	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num9))
	{
		currentAngle = Angle::BOTTOM;

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
