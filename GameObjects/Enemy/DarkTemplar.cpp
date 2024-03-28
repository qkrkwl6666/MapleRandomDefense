#include "pch.h"
#include "DarkTemplar.h"

DarkTemplar::DarkTemplar(const std::string& name, const std::string& animationName)
	: Enemy(name, "DarkTemplar")
{
	armor = ArmorType::SMALL;
	hp = 200.f;
	nickName = L"½ºÄÌ·¹Åæ Àå±³";
	warframePath = "graphics/Enemy/DarkTemplarWarframe.png";
}

DarkTemplar::~DarkTemplar()
{
}

void DarkTemplar::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/DarkTemplar.png");

	GetSprite()->setTextureRect({ 0, 0,	57,	62});

	SetOrigin(Origins::MC);

	SetScale({ 1.5f , 1.5f });
	isSelectSprite->SetScale({ 1.5f,1.5f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/DarkTemplar.csv"));
	animator->Play("DarkTemplarMove", true, true, currentAngle);
}

void DarkTemplar::Reset()
{
	Enemy::Reset();
}

void DarkTemplar::Update(float dt)
{
	Enemy::Update(dt);
	isSelectSprite->SetPosition({ GetPosition().x , GetPosition().y + 25.f });
}

void DarkTemplar::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void DarkTemplar::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
