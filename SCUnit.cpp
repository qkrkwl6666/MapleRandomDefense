#include "pch.h"
#include "SCUnit.h"

SCUnit::SCUnit(const std::string& name) : SpriteAnimatorGo(name)
{

}

SCUnit::~SCUnit()
{
	
}

void SCUnit::Init()
{
	SpriteAnimatorGo::Init();

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Hydralisk.csv"));
	animator->Play("Hydralisk");

}

void SCUnit::Reset()
{
	SpriteAnimatorGo::Reset();
}

void SCUnit::Update(float dt)
{
	SpriteGo::Update(dt);

	animator->Update(dt, currentAngle);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		currentAngle = Angle::TOP;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		currentAngle = Angle::TOP15;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		currentAngle = Angle::TOP30;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
	{
		currentAngle = Angle::TOP60;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num5))
	{
		currentAngle = Angle::RIGHT;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num6))
	{
		currentAngle = Angle::BOTTOM60;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num7))
	{
		currentAngle = Angle::BOTTOM30;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num8))
	{
		currentAngle = Angle::BOTTOM15;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num9))
	{
		currentAngle = Angle::BOTTOM;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num0))
	{
		animator->Stop();
	}


}

void SCUnit::LateUpdate(float dt)
{
	SpriteAnimatorGo::LateUpdate(dt);
}

void SCUnit::Draw(sf::RenderWindow& window)
{
	SpriteAnimatorGo::Draw(window);
}
