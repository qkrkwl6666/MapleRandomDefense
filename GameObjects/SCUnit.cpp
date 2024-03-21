#include "pch.h"
#include "SCUnit.h"
#include "Crosshair.h"
#include "ShapeGo.h"

SCUnit::SCUnit(const std::string& name , const std::string& animationName) 
	: SpriteAnimatorGo(name) , animationName(animationName)
{

}

SCUnit::~SCUnit()
{
	
}

void SCUnit::Init()
{
	SpriteAnimatorGo::Init();
	float aniangle = -157.5;

	while (aniangle <= 180)
	{
		AnimationAngle.push_back(aniangle);
		aniangle += 22.5;
	}

}

void SCUnit::Reset()
{
	SpriteAnimatorGo::Reset();
}

void SCUnit::Update(float dt)
{
	SpriteGo::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right))
	{
		sf::Vector2f direction = FRAMEWORK.GetMouse()->GetPosition() - GetPosition();

		Utils::Normalize(direction);

		std::cout << Utils::Angle(direction) << std::endl;
	
		float aniAngle = Utils::FindNearestAngleconst(AnimationAngle, Utils::Angle(direction));
		std::cout << aniAngle << std::endl;
		currentAngle = angleMap[aniAngle];
		if (aniAngle < -90 || aniAngle > 90)
		{
			SetFlipX(true);
		}
		else
		{
			SetFlipX(false);
		}
	}

	switch (currentStatus)
	{
		case SCUnit::Status::NONE:
			SetStatus(Status::IDLE);
			break;
		case SCUnit::Status::IDLE:
			animator->PlayIdle(animationName + "Move", true, currentAngle);

			//animator->Update(dt, currentAngle);
			break;
		case SCUnit::Status::MOVE:
			if (!animator->IsPlaying())
			{
				animator->Play(animationName + "Move", true, true);
			}
			animator->Update(dt, currentAngle);
			break;
		case SCUnit::Status::ATTACK:
			if (!animator->IsPlaying())
			{
				animator->Play(animationName + "Attack", true, true);
			}
			animator->Update(dt, currentAngle);
			break;
		default:
			break;
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

void SCUnit::SetStatus(Status status)
{
	currentStatus = status;
	if (status == Status::ATTACK)
	{
		animator->Stop();
	}
}
