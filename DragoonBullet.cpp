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
	Translate(direction * speed * dt);
	animator->Update(dt);
	if (Utils::Distance(targetPos,position) < 2.f)
	{
		SetActive(false);
		if (target != nullptr)
		{
			target->OnDamege(damage);
		}
		dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->DeleteGo(this);

	}
}
