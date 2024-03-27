#include "pch.h"
#include "Lurker.h"

Lurker::Lurker(const std::string& name, const std::string& animationName)
	: Enemy(name, "Lurker")
{
	armor = ArmorType::MEDIUM;
	hp = 550.f;
}

Lurker::~Lurker()
{
}

void Lurker::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Lurker.png");

	GetSprite()->setTextureRect({ 0, 0,	72,	67});

	SetOrigin(Origins::MC);

	SetScale({ 1.0f , 1.0f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Lurker.csv"));
	animator->Play("LurkerMove", true, true, currentAngle);
}

void Lurker::Reset()
{
	Enemy::Reset();
}

void Lurker::Update(float dt)
{
	Enemy::Update(dt);
}

void Lurker::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Lurker::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
