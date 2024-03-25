#include "pch.h"
#include "Dragoon.h"
#include "Crosshair.h"
#include "SceneGame.h"
#include "Enemy.h"

Dragoon::Dragoon(const std::string& name, SCUnit::Rarity r)
	: SCUnit(name, "Dragoon")
{
	rarity = r;
}

Dragoon::~Dragoon()
{
}

void Dragoon::Init()
{
	SCUnit::Init();

	SetTexture("graphics/Dragoon.png");

	GetSprite()->setTextureRect({ 0, 0, 65, 65 });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Dragoon.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/DragoonIdle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/DragoonAttack.csv"));

	SetScale({ 1.f , 1.f });
	SetOrigin(Origins::MC);

	type = SCUnit::Type::Dragoon;
}

void Dragoon::Reset()
{
	SCUnit::Reset();
}

void Dragoon::Update(float dt)
{
	SpriteGo::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && isSelect)
	{
		Astar(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos());
		animator->Stop();
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::Space))
	{
		if (isSelectSprite->GetActive() && isSelect)
		{
			SetSelect(false);
		}
		else
		{
			SetSelect(true);
		}
	}

	if (isSelectSprite->GetActive() && isSelect)
	{
		isSelectSprite->SetPosition({ GetPosition().x + 5.f, GetPosition().y + 30.f });
	}

	switch (currentStatus)
	{
	case SCUnit::Status::NONE:

		SetStatus(Status::IDLE);
		break;
	case SCUnit::Status::IDLE:
		if (isAster == true)
		{
			SetStatus(Status::MOVE);
			isAster = false;
			break;
		}
		if (!animator->IsPlaying())
		{
			animator->PlayIdle(animationName + "Idle", true, currentAngle);
		}

		animator->Update(dt, currentAngle);
		break;
	case SCUnit::Status::MOVE:
		if (!animator->IsPlaying())
		{
			animator->Play(animationName + "Move", true, true);
		}

		if (!path.empty())
		{
			if (pathIndex < path.size())
			{
				sf::Vector2f targetPosition = sf::Vector2f(path[pathIndex].x, path[pathIndex].y);

				sf::Vector2f direction = Utils::GetNormalize(targetPosition - GetPosition());

				float aniAngle = Utils::FindNearestAngleconst(AnimationAngle, Utils::Angle(direction));

				float distance = Utils::Distance(targetPosition, GetPosition());

				currentAngle = angleMap[aniAngle];
				if (aniAngle < -90 || aniAngle > 90)
				{
					SetFlipX(true);
				}
				else
				{
					SetFlipX(false);
				}

				if (distance > 0.1f)
				{
					Translate(direction * moveSpeed * dt);
				}
				else
				{
					pathIndex++;
				}
			}
			else
			{
				pathIndex = 0;
				isAster = false;
				SetStatus(Status::IDLE);
				animator->Stop();
			}
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

	if (target == nullptr)
	{
		target = sceneGame->FindEnemy(GetPosition(), attackRange);
	}
	else
	{
		direction = target->GetPosition() - GetPosition();
		Utils::Normalize(direction);
		float aniAngle = Utils::FindNearestAngleconst(AnimationAngle, Utils::Angle(direction));
		currentAngle = angleMap[aniAngle];
		if (aniAngle < -90 || aniAngle > 90)
		{
			SetFlipX(true);
		}
		else
		{
			SetFlipX(false);
		}
		if ((Utils::Distance(GetPosition(), target->GetPosition()) > attackRange * 32))
		{
			target = nullptr;
		}
	}
}

void Dragoon::LateUpdate(float dt)
{
	SCUnit::LateUpdate(dt);
}

void Dragoon::Draw(sf::RenderWindow& window)
{
	SCUnit::Draw(window);
}
