#include "pch.h"
#include "Defiler.h"

Defiler::Defiler(const std::string& name, const std::string& animationName)
	: Enemy(name, "Defiler")
{
	armor = ArmorType::SMALL;
	hp = 1700.f;
}

Defiler::~Defiler()
{
}

void Defiler::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Defiler.png");

	GetSprite()->setTextureRect({ 0, 0,	72,	62});

	SetOrigin(Origins::MC);

	SetScale({ 1.5f , 1.5f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Defiler.csv"));
	animator->Play("DefilerMove", true, true, currentAngle);
}

void Defiler::Reset()
{
	Enemy::Reset();
}

void Defiler::Update(float dt)
{
	Enemy::Update(dt);
}

void Defiler::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Defiler::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
