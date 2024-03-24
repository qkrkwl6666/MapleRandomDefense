#include "pch.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "ShapeGo.h"
#include "SceneGame.h"

Enemy::Enemy(const std::string& name, const std::string& animationName)
	: SpriteAnimatorGo(name), animationName(animationName)
{
}

Enemy::~Enemy()
{
    for (auto unit : sceneGame->GetHydraliskList())
    {
        if (unit->GetTarget() == this)
        {
            unit->SetTarget(nullptr);
        }
    }
    for (auto unit : sceneGame->GetDragoonList())
    {
        if (unit->GetTarget() == this)
        {
            unit->SetTarget(nullptr);
        }
    }
    for (auto unit : sceneGame->GetGhostList())
    {
        if (unit->GetTarget() == this)
        {
            unit->SetTarget(nullptr);
        }
    }
}

void Enemy::Init()
{
	SpriteAnimatorGo::Init();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));

	////////////////////
	SetTexture("graphics/EnemyTest.png");//
	SetOrigin(Origins::MC);//TO-DO 데이터 테이블에 옮겨놓기
	///////////////////


	float aniangle = -157.5;

	while (aniangle <= 180)
	{
		AnimationAngle.push_back(aniangle);
		aniangle += 22.5;
	}

}

void Enemy::Reset()
{
	SpriteAnimatorGo::Reset();
}

void Enemy::Update(float dt)
{
	SpriteAnimatorGo::Update(dt);


    if (InputMgr::GetKey(sf::Keyboard::Left))
    {
        position.x -= 100.f * dt;
        SetPosition(position);
    }

    if (InputMgr::GetKey(sf::Keyboard::Right))
    {
        position.x += 100.f * dt;
        SetPosition(position);
    }

    if (InputMgr::GetKey(sf::Keyboard::Down))
    {
        position.y += 100.f * dt;
        SetPosition(position);
    }

    if (InputMgr::GetKey(sf::Keyboard::Up))
    {
        position.y -= 100.f * dt;
        SetPosition(position);
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
