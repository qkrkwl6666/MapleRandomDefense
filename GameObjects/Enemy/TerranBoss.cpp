#include "pch.h"
#include "TerranBoss.h"
#include "SceneGame.h"
#include "Interface.h"

TerranBoss::TerranBoss(const std::string& name, const std::string& animationName)
	: Enemy(name, "TerranBoss")
{
	hp = 500000.f;
	armor = ArmorType::LARGE;
	enemyType = EnemyType::BOSS;
	nickName = L"시그너스";
	warframePath = "graphics/Enemy/TerranBossWarframe.png";
}

TerranBoss::~TerranBoss()
{

}

void TerranBoss::Init()
{
	Enemy::Init();

	SetTexture("graphics/Enemy/TerranBoss.png");

	SetScale({ 1.f , 1.f });

	SetOrigin(Origins::MC);
	isSelectSprite->SetScale({ 5.f,5.f });
}

void TerranBoss::Reset()
{
	Enemy::Reset();
}

void TerranBoss::Update(float dt)
{
	SpriteGo::Update(dt);
	isSelectSprite->SetPosition({ GetPosition().x , GetPosition().y + 30.f });

	if (hp <= 0)
	{
		Dead();
	}
	if (Dir == 3 || Dir == 6 || Dir == 7)
	{
		SetFlipX(true);
	}
	else
	{
		SetFlipX(false);
	}

	switch (Dir)
	{
		case (int)Dir::LEFT:
			if (GetPosition().x <= changeDirPos[0].x)
			{
				SetPosition({ changeDirPos[0].x , changeDirPos[0].y });
				Dir = (int)Dir::LEFT_DOWN;
				currentDirection = front[Dir];
				currentAngle = angleMMap[Dir];
				break;
			}
			Translate(currentDirection * dt * moveSpeed);
			break;

		case (int)Dir::LEFT_DOWN:
			if (GetPosition().y >= changeDirPos[1].y)
			{
				SetPosition({ changeDirPos[1].x , changeDirPos[1].y });
				Dir = (int)Dir::DOWN;
				currentDirection = front[Dir];
				currentAngle = angleMMap[Dir];
				break;
			}
			Translate(currentDirection * dt * (moveSpeed / 2.f));
			break;

		case (int)Dir::DOWN:
			if (GetPosition().y >= changeDirPos[2].y)
			{
				SetPosition({ changeDirPos[2].x , changeDirPos[2].y });
				Dir = (int)Dir::RIGHT_DOWN;
				currentDirection = front[Dir];
				currentAngle = angleMMap[Dir];
				break;
			}
			Translate(currentDirection * dt * moveSpeed);
			break;

		case (int)Dir::RIGHT_DOWN:
			if (GetPosition().y >= changeDirPos[3].y)
			{
				SetPosition({ changeDirPos[3].x , changeDirPos[3].y });
				Dir = (int)Dir::RIGHT;
				currentDirection = front[Dir];
				currentAngle = angleMMap[Dir];
				break;
			}
			Translate(currentDirection * dt * (moveSpeed / 2.f));
			break;

		case (int)Dir::RIGHT:
			if (GetPosition().x >= changeDirPos[4].x)
			{
				SetPosition({ changeDirPos[4].x , changeDirPos[4].y });
				Dir = (int)Dir::RIGHT_TOP;
				currentDirection = front[Dir];
				currentAngle = angleMMap[Dir];
				break;
			}
			Translate(currentDirection * dt * moveSpeed);
			break;

		case (int)Dir::RIGHT_TOP:
			if (GetPosition().y <= changeDirPos[5].y)
			{
				SetPosition({ changeDirPos[5].x , changeDirPos[5].y });
				Dir = (int)Dir::TOP;
				currentDirection = front[Dir];
				currentAngle = angleMMap[Dir];
				break;
			}
			Translate(currentDirection * dt * (moveSpeed / 2.f));
			break;

		case (int)Dir::TOP:
			if (GetPosition().y <= changeDirPos[6].y)
			{
				SetPosition({ changeDirPos[6].x , changeDirPos[6].y });
				Dir = (int)Dir::LEFT_TOP;
				currentDirection = front[Dir];
				currentAngle = angleMMap[Dir];
				break;
			}
			Translate(currentDirection * dt * moveSpeed);
			break;

		case (int)Dir::LEFT_TOP:
			if (GetPosition().y <= changeDirPos[7].y)
			{
				SetPosition({ changeDirPos[7].x , changeDirPos[7].y });
				Dir = (int)Dir::LEFT;
				currentDirection = front[Dir];
				currentAngle = angleMMap[Dir];
				break;
			}
			Translate(currentDirection * dt * (moveSpeed / 2.f));
			break;
	}

	if (
		dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetInterface()->GetUiTarget()
		!= this)
	{
		SetSelect(false);
	}
}

void TerranBoss::LateUpdate(float dt)
{
	//Enemy::LateUpdate(dt);
}

void TerranBoss::Draw(sf::RenderWindow& window)
{
	Enemy::Draw(window);
}
