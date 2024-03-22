#include "pch.h"
#include "SCUnit.h"
#include "Crosshair.h"
#include "ShapeGo.h"
#include "SceneGame.h"

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
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));

	float aniangle = -157.5;

	while (aniangle <= 180)
	{
		AnimationAngle.push_back(aniangle);
		aniangle += 22.5;
	}

	// ���� ��������Ʈ
	isSelectSprite = std::make_shared<SpriteGo>();
	isSelectSprite->SetTexture("graphics/UI/cursorsSelect.png");
	isSelectSprite->SetOrigin(Origins::MC);
	isSelectSprite->SetScale({ 2.f , 2.f });
	isSelectSprite->SetActive(false);

}

void SCUnit::Reset()
{
	SpriteAnimatorGo::Reset();
}

void SCUnit::Update(float dt)
{
	SpriteGo::Update(dt);
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
	if (isSelectSprite->GetActive() && isSelect == true)
	{
		isSelectSprite->Draw(window);
	}

	SpriteAnimatorGo::Draw(window);
}

void SCUnit::SellThis()
{
	//TO-DO ������ ���� �ִϸ��̼� ���
	sceneGame->SetMineral(sceneGame->GetMineral() + sellingValue); // �ڽ��� �ǸŰ���
	sceneGame->message(SceneGame::MessageType::SellUnit);
	sceneGame->message(sellingValue);

	sceneGame->RemoveGo(this);
}

void SCUnit::SetStatus(Status status)
{
	currentStatus = status;
	if (status == Status::ATTACK)
	{
		animator->Stop();
	}
}

void SCUnit::SetSelect(bool isSelect)
{
	this->isSelect = isSelect;
	isSelectSprite->SetActive(isSelect);
}
