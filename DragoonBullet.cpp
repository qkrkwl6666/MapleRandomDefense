#include "pch.h"
#include "DragoonBullet.h"
#include "Enemy.h"

DragoonBullet::DragoonBullet(const std::string& name, const std::string& animationName)
	: SpriteAnimatorGo(name), animationName(animationName)
{
}

DragoonBullet::~DragoonBullet()
{
}

void DragoonBullet::Init(Enemy* t, int d)
{
	target = t;
	damage = d;
	targetPos = target->GetPosition();
	direction = targetPos - position;
	Utils::Normalize(direction);
}

void DragoonBullet::Update(float dt)
{
	Translate(direction * speed * dt);

	if (position == targetPos)
	{
		delete(this);
		if (target != nullptr)
		{
			target->OnDamege(damage);
		}
	}
}
