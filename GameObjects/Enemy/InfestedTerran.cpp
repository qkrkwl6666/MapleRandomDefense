#include "pch.h"
#include "InfestedTerran.h"

InfestedTerran::InfestedTerran(const std::string& name, const std::string& animationName)
	: Enemy(name, "InfestedTerran")
{
	armor = ArmorType::SMALL;
	hp = 700.f;
}

InfestedTerran::~InfestedTerran()
{
}

void InfestedTerran::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/InfestedTerran.png");

	GetSprite()->setTextureRect({ 0, 0,	41,	54});

	SetOrigin(Origins::MC);

	SetScale({ 1.5f , 1.5f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/InfestedTerran.csv"));
	animator->Play("InfestedTerranMove", true, true, currentAngle);
}

void InfestedTerran::Reset()
{
	Enemy::Reset();
}

void InfestedTerran::Update(float dt)
{
	Enemy::Update(dt);
}

void InfestedTerran::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void InfestedTerran::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
