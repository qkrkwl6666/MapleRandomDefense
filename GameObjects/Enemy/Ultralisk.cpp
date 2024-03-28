#include "pch.h"
#include "Ultralisk.h"

Ultralisk::Ultralisk(const std::string& name, const std::string& animationName)
	: Enemy(name, "Ultralisk")
{
	armor = ArmorType::LARGE;
	hp = 60.f;
	nickName = L"와일드보어";
	warframePath = "graphics/Enemy/UltraliskWarframe.png";
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
	isSelectSprite->SetScale({ 2.f,2.f });
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
	isSelectSprite->SetPosition({ GetPosition().x , GetPosition().y + 16.f });
}

void Ultralisk::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Ultralisk::Draw(sf::RenderWindow & window)
{
	Enemy::Draw(window);
}
