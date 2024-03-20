#include "pch.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "rapidcsv.h"

SceneTitle::SceneTitle(SceneIds id)
	:Scene(id)
{

}

void SceneTitle::Init()
{
	uiTitle = new TextGo("uiTitle");
	uiTitle->Set(RES_MGR_FONT.Get("font/NotoSansKR-Regular.otf"), "Press Enter to Animation Editor", 40, sf::Color::White);
	uiTitle->SetOrigin(Origins::MC);
	uiTitle->SetPosition(GetViewCenter());
	AddGo(uiTitle);

	uiTitle2 = new TextGo("uiTitle2");
	uiTitle2->Set(RES_MGR_FONT.Get("font/NotoSansKR-Regular.otf"), "Press F2 to Map Editor", 40, sf::Color::White);
	uiTitle2->SetOrigin(Origins::MC);
	uiTitle2->SetPosition({ GetViewCenter().x, GetViewCenter().y + 90});
	AddGo(uiTitle2);
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

	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		std::cout << "ChangeScene!!" << std::endl;
		SCENE_MGR.ChangeScene(SceneIds::SceneTilemapEditor);
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
