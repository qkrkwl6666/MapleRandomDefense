#include "pch.h"
#include "Queen.h"

Queen::Queen(const std::string& name, const std::string& animationName)
	: Enemy(name, "Queen")
{
	armor = ArmorType::LARGE;
	hp = 250.f;
	nickName = L"주니어 레이스";
	warframePath = "graphics/Enemy/QueenWarframe.png";
}

Queen::~Queen()
{
}

void Queen::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Queen.png");

	GetSprite()->setTextureRect({ 0, 0, 78, 71});

	SetOrigin(Origins::MC);

	SetScale({ 1.0f , 1.0f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Queen.csv"));
	animator->Play("QueenMove", true, true, currentAngle);
}

void Queen::Reset()
{
	Enemy::Reset();
}

void Queen::Update(float dt)
{
	Enemy::Update(dt);
	isSelectSprite->SetPosition({ GetPosition().x , GetPosition().y + 15.f });
}

void Queen::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Queen::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
