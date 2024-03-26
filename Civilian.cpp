#include "pch.h"
#include "Civilian.h"
#include "SceneGame.h"

Civilian::Civilian(const std::string& name, const std::string& animationName)
	: SCUnit(name , "Civilian")
{
}

Civilian::~Civilian()
{
}

void Civilian::Init()
{
	SCUnit::Init();

	SetTexture("graphics/Terran Civilian.png");

	GetSprite()->setTextureRect({ 0, 0, 24, 35 });

	animator->AddClip(RES_MGR_ANIMATIONCLIP.Get("Animation/AnimatorEditer/Terran Civilian.csv"));

	SetScale({ 1.f , 1.f });

	SetOrigin(Origins::MC);

	type = SCUnit::Type::Civilian;
}


void Civilian::Reset()
{
	SCUnit::Reset();
}

void Civilian::Update(float dt)
{
	SCUnit::Update(dt);
}

void Civilian::LateUpdate(float dt)
{
	SCUnit::LateUpdate(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Right) && isSelect)
	{
		Astar(dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame))->GetWorldMousePos());
	}


}

void Civilian::Draw(sf::RenderWindow& window)
{
	SCUnit::Draw(window);
}
