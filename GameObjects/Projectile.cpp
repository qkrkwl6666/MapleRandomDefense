#include "pch.h"
#include "Projectile.h"

Projectile::Projectile(const std::string& name)
{

}

Projectile::~Projectile()
{

}

void Projectile::Init()
{
	SpriteAnimatorGo::Init();

	//SetTexture("graphics/HydraliskProjectile.png");
}

void Projectile::Reset()
{
	SpriteAnimatorGo::Reset();
}

void Projectile::Update(float dt)
{
	SpriteAnimatorGo::Update(dt);
}

void Projectile::LateUpdate(float dt)
{
	SpriteAnimatorGo::LateUpdate(dt);
}

void Projectile::Draw(sf::RenderWindow& window)
{
	SpriteAnimatorGo::Draw(window);
}
