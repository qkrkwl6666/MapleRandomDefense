#include "pch.h"
#include "Hydralisk.h"
#include "Crosshair.h"

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
	
	SetScale({ 2.f , 2.f });
	SetOrigin(Origins::MC);

	type = SCUnit::Type::Hydralisk;
}

void Hydralisk::Reset()
{
	SCUnit::Reset();
}

void Hydralisk::Update(float dt)
{
	SCUnit::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		currentAngle = Angle::TOP;
		SetStatus(Status::ATTACK);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		currentAngle = Angle::TOP15;
		SetStatus(Status::MOVE);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		currentAngle = Angle::TOP30;
		SetStatus(Status::MOVE);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
	{
		currentAngle = Angle::TOP60;
		SetStatus(Status::MOVE);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num5))
	{
		currentAngle = Angle::RIGHT;
		SetStatus(Status::IDLE);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num6))
	{
		currentAngle = Angle::BOTTOM60;
		SetStatus(Status::MOVE);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num7))
	{
		currentAngle = Angle::BOTTOM30;
		SetStatus(Status::MOVE);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num8))
	{
		currentAngle = Angle::BOTTOM15;
		SetStatus(Status::MOVE);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num9))
	{
		currentAngle = Angle::BOTTOM;
		SetStatus(Status::MOVE);
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
