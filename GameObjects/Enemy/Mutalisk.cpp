#include "pch.h"
#include "Mutalisk.h"

Mutalisk::Mutalisk(const std::string& name, const std::string& animationName)
	: Enemy(name, "Mutalisk")
{
	armor = ArmorType::MEDIUM;
	hp = 400.f;
}

Mutalisk::~Mutalisk()
{
}

void Mutalisk::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Mutalisk.png");

	GetSprite()->setTextureRect({ 0, 0,	67,	75});

	SetOrigin(Origins::MC);

	SetScale({ 1.0f , 1.0f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Mutalisk.csv"));
	animator->Play("MutaliskMove", true, true, currentAngle);
}

void Mutalisk::Reset()
{
	Enemy::Reset();
}

void Mutalisk::Update(float dt)
{
	Enemy::Update(dt);
}

void Mutalisk::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Mutalisk::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
