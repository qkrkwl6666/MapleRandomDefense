#include "pch.h"
#include "Enemy.h"
#include "Crosshair.h"
#include "ShapeGo.h"
#include "SceneGame.h"

Enemy::Enemy(const std::string& name, const std::string& animationName)
	: SCUnit(name, "Zergling")
{
}

Enemy::~Enemy()
{

}

void Enemy::Init()
{
	SCUnit::Init();


}

void Enemy::Reset()
{
	SCUnit::Reset();
}

void Enemy::Update(float dt)
{
	SCUnit::Update(dt);

}

void Enemy::LateUpdate(float dt)
{
	SCUnit::LateUpdate(dt);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	SCUnit::Draw(window);
}
