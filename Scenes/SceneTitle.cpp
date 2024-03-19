#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "rapidcsv.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{

}

void SceneTitle::Init()
{

	Scene::Init();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) 
	{
		std::cout << "ChangeScene!!" << std::endl;
		SCENE_MGR.ChangeScene(SceneIds::SceneAnimatorEditer);
	}

}

void SceneTitle::Enter()
{
	Scene::Enter();
}

void SceneTitle::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);
}
