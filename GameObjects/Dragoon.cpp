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
	hitBox.setSize({ 30.f,30.f });
	hitBox.setOrigin(hitBox.getSize() / 2.f);
	GetSprite()->setTextureRect({ 0, 0, 65, 65 });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Dragoon.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/DragoonIdle.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/DragoonAttack.csv"));

	isSelectSprite->SetScale({ 2.f , 2.f });

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
	hitBox.setPosition(position);
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
		isSelectSprite->SetPosition({ hitBox.getPosition().x, hitBox.getPosition().y + 10.f });
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
			animator->Play(animationName + "Idle", true, false);
		}

		animator->Update(dt);
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

	//********* 面倒贸府 **********
	for (auto go : sceneGame->GetAllUnitList())
	{
		if (go == this)
		{
			continue;
		}
		sf::FloatRect thisBounds = hitBox.getGlobalBounds();
		sf::FloatRect otherBounds = go->GetHitBox().getGlobalBounds();
		if (thisBounds.intersects(otherBounds) && currentStatus == SCUnit::Status::MOVE) // 面倒 矫
		{
			stuckTimer += dt;
			float left = otherBounds.left + otherBounds.width - thisBounds.left;
			float right = thisBounds.left + thisBounds.width - otherBounds.left;
			float top = otherBounds.top + otherBounds.height - thisBounds.top;
			float bottom = thisBounds.top + thisBounds.height - otherBounds.top;

			if (left < right && left < top && left < bottom)
			{
				SetPosition({ position.x + left , position.y });
			}
			else if (right < left && right < top && right < bottom)
			{
				SetPosition({ position.x - right , position.y });
			}
			else if (top < left && top < right && top < bottom)
			{
				SetPosition({ position.x, position.y + top });
			}
			else
			{
				SetPosition({ position.x, position.y - bottom });
			}
		}
		if (stuckTimer > 2.f)
		{
			isAster = false;
			animator->Play(animationName + "Idle", true, false);
			SetStatus(SCUnit::Status::IDLE);
			stuckTimer = 0;
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
