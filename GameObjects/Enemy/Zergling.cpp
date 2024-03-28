#include "pch.h"
#include "Zergling.h"

Zergling::Zergling(const std::string& name, const std::string& animationName)
	: Enemy(name , "Zergling")
{
	armor = ArmorType::SMALL;
	hp = 10.f;
	nickName = L"������";
	warframePath = "graphics/Enemy/ZerglingWarframe.png";
}

Zergling::~Zergling()
{
}

void Zergling::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/Zergling.png");

	GetSprite()->setTextureRect({ 0, 0,	43,	42});

	SetOrigin(Origins::MC);

	SetScale({ 1.5f , 1.5f });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Zergling.csv"));
	animator->Play("ZerglingMove" ,true , true ,currentAngle);
	
}

void Zergling::Reset()
{
	Enemy::Reset();
}

void Zergling::Update(float dt)
{
	Enemy::Update(dt);
	isSelectSprite->SetPosition({ GetPosition().x , GetPosition().y + 10.f });
}

void Zergling::LateUpdate(float dt)
{
	Enemy::LateUpdate(dt);
}

void Zergling::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
