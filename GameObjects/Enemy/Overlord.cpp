#include "pch.h"
#include "Overlord.h"

Overlord::Overlord(const std::string& name, const std::string& animationName)
	: Enemy(name, "Overlord")
{
	armor = ArmorType::LARGE;
	hp = 400.f;
	nickName = L"¾öÆ¼";
	warframePath = "graphics/Enemy/OverlordWarframe.png";
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
	isSelectSprite->SetScale({ 2.f,2.f });

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
	isSelectSprite->SetPosition({ GetPosition().x , GetPosition().y + 15.f });
}

void Overlord::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Overlord::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
