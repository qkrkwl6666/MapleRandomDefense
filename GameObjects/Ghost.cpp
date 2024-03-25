#include "pch.h"
#include "Ghost.h"
#include "Crosshair.h"
#include "SceneGame.h"

Ghost::Ghost(const std::string& name, SCUnit::Rarity r)
	: SCUnit(name, "Ghost")
{
	rarity = r;
}

Ghost::~Ghost()
{
}

void Ghost::Init()
{
	SCUnit::Init();

	SetTexture("graphics/Ghost.png");

	GetSprite()->setTextureRect({ 0, 114, 42, 38 });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Ghost.csv"));
	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/GhostAttack.csv"));

	SetScale({ 1.f , 1.f });
	SetOrigin(Origins::MC);

	type = SCUnit::Type::Ghost;
}

void Ghost::Reset()
{
	SCUnit::Reset();
}

void Ghost::Update(float dt)
{
	SCUnit::Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && isSelect)
	{
		Astar(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos());
	}
}

void Ghost::LateUpdate(float dt)
{
	SCUnit::LateUpdate(dt);
}

void Ghost::Draw(sf::RenderWindow& window)
{
	SCUnit::Draw(window);
}
