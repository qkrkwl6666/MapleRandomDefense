#include "pch.h"
#include "Devourer.h"

Devourer::Devourer(const std::string& name, const std::string& animationName)
	: Enemy(name, "Devourer")
{
	armor = ArmorType::LARGE;
	hp = 1300.f;
	nickName = L"콜드아이";
	warframePath = "graphics/Enemy/DevourerWarframe.png";
}

Devourer::~Devourer()
{
}

void Devourer::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Devourer.png");

	GetSprite()->setTextureRect({ 0, 0,	73,	86});

	SetOrigin(Origins::MC);

	SetScale({ 1.5f , 1.5f });
	isSelectSprite->SetScale({ 2.5f,2.5f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Devourer.csv"));
	animator->Play("DevourerMove", true, true, currentAngle);
}

void Devourer::Reset()
{
	Enemy::Reset();
}

void Devourer::Update(float dt)
{
	Enemy::Update(dt);
	isSelectSprite->SetPosition({ GetPosition().x , GetPosition().y + 15.f });
}

void Devourer::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Devourer::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
