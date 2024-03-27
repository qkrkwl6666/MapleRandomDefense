#include "pch.h"
#include "Scourge.h"

Scourge::Scourge(const std::string& name, const std::string& animationName)
	: Enemy(name, "Scourge")
{
	armor = ArmorType::SMALL;
	hp = 80.f;
}

Scourge::~Scourge()
{

}

void Scourge::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Scourge.png");

	GetSprite()->setTextureRect({ 0	,0,	34,	30 });

	SetOrigin(Origins::MC);

	SetScale({ 1.5f , 1.5f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Scourge.csv"));
	animator->Play("ScourgeMove", true, true, currentAngle);
}

void Scourge::Reset()
{
	Enemy::Reset();
}

void Scourge::Update(float dt)
{
	Enemy::Update(dt);
}

void Scourge::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Scourge::Draw(sf::RenderWindow & window)
{
	Enemy::Draw(window);
}
