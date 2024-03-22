#include "pch.h"
#include "Building.h"
#include "SceneGame.h"


Building::Building(const std::string& name) : SpriteGo(name)
{
}

void Building::Init()
{
	SpriteGo::Init();
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetScene(SceneIds::SceneGame));

}

void Building::Reset()
{
	SpriteGo::Reset();
}

void Building::Update(float dt)
{
	SpriteGo::Update(dt);
}

void Building::LateUpdate(float dt)
{
	SpriteGo::LateUpdate(dt);
}
