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

}

void Projectile::Reset()
{
	SpriteAnimatorGo::Reset();
}

void Projectile::Update(float dt)
{
	SpriteGo::Update(dt);

	animator->Update(dt);
}

void Projectile::Update(float dt , Angle angle)
{
	SpriteGo::Update(dt);

	animator->Update(dt, angle);
}

void Projectile::LateUpdate(float dt)
{
	SpriteAnimatorGo::LateUpdate(dt);
}

void Projectile::Draw(sf::RenderWindow& window)
{
	SpriteAnimatorGo::Draw(window);
}
