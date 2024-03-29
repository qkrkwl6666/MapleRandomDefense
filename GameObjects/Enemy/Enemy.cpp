#include "pch.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "ShapeGo.h"
#include "SceneGame.h"
#include "Interface.h"

Enemy::Enemy(const std::string& name, const std::string& animationName)
	: SpriteAnimatorGo(name), animationName(animationName)
{
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{
	SpriteAnimatorGo::Init();
	hpMax = hp;

	float aniangle = -157.5;
	while (aniangle <= 180)
	{
		AnimationAngle.push_back(aniangle);
		aniangle += 22.5;
	}

	SetPosition({ 16 * 32 + 16.f , 9 * 32 + 16.f });

	changeDirPos.push_back({ 12.f * 32.f + 16.f, 9 * 32.f + 16.f });
	changeDirPos.push_back({ 9.f * 32.f + 16.f, 12 * 32.f + 16.f });
	changeDirPos.push_back({ 9.f * 32.f + 16.f, 21 * 32.f + 16.f });
	changeDirPos.push_back({ 12.f * 32.f + 16.f, 24 * 32.f + 16.f });
	changeDirPos.push_back({ 21.f * 32.f + 16.f, 24 * 32.f + 16.f });
	changeDirPos.push_back({ 24.f * 32.f + 16.f, 21 * 32.f + 16.f });
	changeDirPos.push_back({ 24.f * 32.f + 16.f, 12 * 32.f + 16.f });
	changeDirPos.push_back({ 21.f * 32.f + 16.f, 9 * 32.f + 16.f });

	currentDirection = front[Dir];
	currentAngle = angleMMap[Dir];

	isSelectSprite = std::make_shared<SpriteGo>();
	isSelectSprite->SetTexture("graphics/UI/EnemySelect.png");
	isSelectSprite->SetScale({ 1.5f , 1.5f });
	isSelectSprite->SetOrigin(Origins::MC);
	isSelectSprite->SetActive(false);
}

void Enemy::Reset()
{
	SpriteAnimatorGo::Reset();
}

void Enemy::Update(float dt)
{
	SpriteGo::Update(dt);

	animator->Update(dt, currentAngle);

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

void Enemy::LateUpdate(float dt)
{
	SpriteAnimatorGo::LateUpdate(dt);


}

void Enemy::Draw(sf::RenderWindow& window)
{
	if (isSelectSprite->GetActive() && isSelect == true)
	{
		isSelectSprite->Draw(window);
	}
	SpriteAnimatorGo::Draw(window);
}

void Enemy::OnDamege(float damage, SCUnit::Type t)
{
	switch (armor)
	{
	case Enemy::ArmorType::SMALL:
		switch (t)
		{
		case SCUnit::Type::Hydralisk:
			hp -= damage;
			break;
		case SCUnit::Type::Dragoon:
			hp -= (damage / 2);
			break;
		case SCUnit::Type::Ghost:
			hp -= damage;
			break;
		}
		break;
	case Enemy::ArmorType::MEDIUM:
		switch (t)
		{
		case SCUnit::Type::Hydralisk:
			hp -= damage;
			break;
		case SCUnit::Type::Dragoon:
			hp -= ((damage / 4) * 3);
			break;
		case SCUnit::Type::Ghost:
			hp -= ((damage / 4) * 3);
			break;
		}
		break;
	case Enemy::ArmorType::LARGE:
		switch (t)
		{
		case SCUnit::Type::Hydralisk:
			hp -= damage;
			break;
		case SCUnit::Type::Dragoon:
			hp -= damage;
			break;
		case SCUnit::Type::Ghost:
			hp -= (damage / 2);
			break;
		}
		break;
	}
}

void Enemy::Dead()
{
	dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GasUp();
	dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->DeleteGo(this);
	if (
		dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetInterface()->GetUiTarget()
		== this)
	{
		dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetInterface()->SetUiTarget(nullptr);
	}
	SetActive(false);
}

void Enemy::SetSelect(bool isSelect)
{
	this->isSelect = isSelect;
	isSelectSprite->SetActive(isSelect);
}
