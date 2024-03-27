#include "pch.h"
#include "Zealot.h"

Zealot::Zealot(const std::string& name, const std::string& animationName)
	: Enemy(name, "Zealot")
{
	armor = ArmorType::SMALL;
	hp = 2000.f;
}

Zealot::~Zealot()
{
}

void Zealot::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Zealot.png");

	GetSprite()->setTextureRect({ 0, 0,	41,	44 });

	SetOrigin(Origins::MC);

	SetScale({ 1.5f , 1.5f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Zealot.csv"));
	animator->Play("ZealotMove", true, true, currentAngle);
}

void Zealot::Reset()
{
	Enemy::Reset();
}

void Zealot::Update(float dt)
{
	Enemy::Update(dt);
}

void Zealot::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Zealot::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
