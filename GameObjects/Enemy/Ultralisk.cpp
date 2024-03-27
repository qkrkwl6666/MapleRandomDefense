#include "pch.h"
#include "Ultralisk.h"

Ultralisk::Ultralisk(const std::string& name, const std::string& animationName)
	: Enemy(name, "Ultralisk")
{
	armor = ArmorType::LARGE;
	hp = 60.f;
}

Ultralisk::~Ultralisk()
{

}

void Ultralisk::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Ultralisk.png");

	GetSprite()->setTextureRect({ 0, 0, 101, 108});

	SetOrigin(Origins::MC);

	SetScale({ 1.0f , 1.0f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Ultralisk.csv"));
	animator->Play("UltraliskMove", true, true, currentAngle);
}

void Ultralisk::Reset()
{
	Enemy::Reset();
}

void Ultralisk::Update(float dt)
{
	Enemy::Update(dt);
}

void Ultralisk::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Ultralisk::Draw(sf::RenderWindow & window)
{
	Enemy::Draw(window);
}
