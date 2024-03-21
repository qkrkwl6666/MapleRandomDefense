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
	TitleImage = new SpriteGo("titleImage");
	TitleImage->SetTexture("graphics/Title.png");
	TitleImage->SetOrigin(Origins::MC);
	TitleImage->SetPosition({ GetViewCenter().x, GetViewCenter().y - 150 });
	AddGo(TitleImage);

	uiTitle = new TextGo("ToAnimation");
	uiTitle->Set(RES_MGR_FONT.Get("font/NotoSansKR-Regular.otf"), "Press F1 to Animation Editor", 40, sf::Color::White);
	uiTitle->SetOrigin(Origins::MC);
	uiTitle->SetPosition({ GetViewCenter().x, GetViewCenter().y + 90 });
	AddGo(uiTitle);

	uiTitle2 = new TextGo("ToMap");
	uiTitle2->Set(RES_MGR_FONT.Get("font/NotoSansKR-Regular.otf"), "Press F2 to Map Editor", 40, sf::Color::White);
	uiTitle2->SetOrigin(Origins::MC);
	uiTitle2->SetPosition({ GetViewCenter().x, GetViewCenter().y + 170});
	AddGo(uiTitle2);
	Scene::Init();

	uiTitle3 = new TextGo("ToGame");
	uiTitle3->Set(RES_MGR_FONT.Get("font/NotoSansKR-Regular.otf"), "Press Enter to Game", 70, sf::Color::White);
	uiTitle3->SetOrigin(Origins::MC);
	uiTitle3->SetPosition({ GetViewCenter().x, GetViewCenter().y + 280 });
	AddGo(uiTitle3);
	Scene::Init();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::F1)) 
	{
		std::cout << "ChangeScene!!" << std::endl;
		SCENE_MGR.ChangeScene(SceneIds::SceneAnimatorEditer);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		std::cout << "ChangeScene!!" << std::endl;
		SCENE_MGR.ChangeScene(SceneIds::SceneTilemapEditor);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		std::cout << "ChangeScene!!" << std::endl;
		SCENE_MGR.ChangeScene(SceneIds::SceneGame);
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
