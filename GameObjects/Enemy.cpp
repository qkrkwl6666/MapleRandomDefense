#include "pch.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "ShapeGo.h"
#include "SceneGame.h"

Enemy::Enemy(const std::string& name, const std::string& animationName)
	: SpriteAnimatorGo(name) , animationName(animationName)
{
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{
	SpriteAnimatorGo::Init();

	float aniangle = -157.5;

	while (aniangle <= 180)
	{
		AnimationAngle.push_back(aniangle);
		aniangle += 22.5;
	}

	SetPosition({ 16 * 32 + 16.f , 9 * 32 + 16.f });

	changeDirPos.push_back({12.f * 32.f + 16.f, 9 * 32.f + 16.f});
	changeDirPos.push_back({9.f * 32.f + 16.f, 12 * 32.f + 16.f});
	changeDirPos.push_back({9.f * 32.f + 16.f, 21 * 32.f + 16.f});
	changeDirPos.push_back({12.f * 32.f + 16.f, 24 * 32.f + 16.f});
	changeDirPos.push_back({21.f * 32.f + 16.f, 24 * 32.f + 16.f});
	changeDirPos.push_back({24.f * 32.f + 16.f, 21 * 32.f + 16.f});
	changeDirPos.push_back({24.f * 32.f + 16.f, 12 * 32.f + 16.f});
	changeDirPos.push_back({21.f * 32.f + 16.f, 9 * 32.f + 16.f});

	currentDirection = front[Dir];
	currentAngle = angleMMap[Dir];
}

void Enemy::Reset()
{
	SpriteAnimatorGo::Reset();
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);

	animator->Update(dt, currentAngle);
	std::cout << hp << std::endl;

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
				SetPosition({ changeDirPos[1].x , changeDirPos[1].y});
				Dir = (int)Dir::DOWN;
				currentDirection = front[Dir];
				currentAngle = angleMMap[Dir];
				break;
			}
			Translate(currentDirection * dt * (moveSpeed / 2));
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
			Translate(currentDirection * dt * (moveSpeed / 2));
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
			Translate(currentDirection * dt * (moveSpeed / 2));
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
			Translate(currentDirection * dt * (moveSpeed / 2));
			break;
	}
}

void Enemy::LateUpdate(float dt)
{
	SpriteAnimatorGo::LateUpdate(dt);

	
}

void Enemy::Draw(sf::RenderWindow& window)
{
	SpriteAnimatorGo::Draw(window);
}

void Enemy::OnDamege(float damage)
{
	if (hp - damage <= 0)
	{
		hp = 0;
		Dead();
	}
	else
	{
		hp -= damage;
	}
}

void Enemy::Dead()
{
	SetActive(false);
}
