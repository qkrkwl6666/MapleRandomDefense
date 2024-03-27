#include "pch.h"
#include "Guardian.h"

Guardian::Guardian(const std::string& name, const std::string& animationName)
	: Enemy(name, "Guardian")
{
	armor = ArmorType::LARGE;
	hp = 1000.f;
}

Guardian::~Guardian()
{
}

void Guardian::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Guardian.png");

	GetSprite()->setTextureRect({ 0,0,	81,	74});

	SetOrigin(Origins::MC);

	SetScale({ 1.5f , 1.5f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Guardian.csv"));
	animator->Play("GuardianMove", true, true, currentAngle);
}

void Guardian::Reset()
{
	Enemy::Reset();
}

void Guardian::Update(float dt)
{
	Enemy::Update(dt);
}

void Guardian::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Guardian::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
