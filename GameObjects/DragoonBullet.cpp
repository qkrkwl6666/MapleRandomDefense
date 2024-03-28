#include "pch.h"
#include "DragoonBullet.h"
#include "Enemy.h"
#include "SceneGame.h"

DragoonBullet::DragoonBullet(const std::string& name, const std::string& animationName)
	: SpriteAnimatorGo(name), animationName(animationName)
{
}

DragoonBullet::~DragoonBullet()
{
}

void DragoonBullet::Init(Enemy* t, int d)
{
	SetTexture("graphics/DragoonBullet.png");
	GetSprite()->setTextureRect({ 0, 0, 32, 32 });
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/DragoonBullet.csv"));

	target = t;
	damage = d;
	targetPos = target->GetPosition();
	direction = targetPos - position;
	Utils::Normalize(direction);
	animator->Play("DragoonBullet", true);
}

void DragoonBullet::Update(float dt)
{
	prevPosition = position;
	Translate(direction * speed * dt);
	animator->Update(dt);
	
	float targetToprePos = Utils::Distance(targetPos, prevPosition);
	float prePosToPos = Utils::Distance(position, prevPosition);
	float targetToPos = Utils::Distance(targetPos, position);

	if (targetToprePos <= prePosToPos)
	{
		position = targetPos;
	}

	if (position == targetPos)
	{
		SetActive(false);
		if (target != nullptr)
		{
			target->OnDamege(damage, SCUnit::Type::Dragoon);
		}
		dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->DeleteGo(this);
	}
}
