#include "pch.h"
#include "Overlord.h"

Overlord::Overlord(const std::string& name, const std::string& animationName)
	: Enemy(name, "Overlord")
{
	armor = ArmorType::LARGE;
	hp = 400.f;
}

Overlord::~Overlord()
{
}

void Overlord::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Overlord.png");

	GetSprite()->setTextureRect({ 0, 0,	66,	64});

	SetOrigin(Origins::MC);

	SetScale({ 1.5f , 1.5f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Overlord.csv"));
	animator->Play("OverlordMove", true, true, currentAngle);
}

void Overlord::Reset()
{
	Enemy::Reset();
}

void Overlord::Update(float dt)
{
	Enemy::Update(dt);
}

void Overlord::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Overlord::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
