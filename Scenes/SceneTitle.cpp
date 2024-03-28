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
	worldView.zoom(1.0f / 0.65f);

	RES_MGR_SOUND_BUFFER.Load("sounds/Lith.mp3");
	RES_MGR_SOUND_BUFFER.Load("sounds/Henesys.mp3");
	RES_MGR_SOUND_BUFFER.Load("sounds/perion.mp3");
	RES_MGR_SOUND_BUFFER.Load("sounds/ellinia.mp3");
	RES_MGR_SOUND_BUFFER.Load("sounds/cunning.mp3");
	RES_MGR_SOUND_BUFFER.Load("sounds/sleepywood.mp3");
	RES_MGR_SOUND_BUFFER.Load("sounds/elnath.mp3");
	RES_MGR_SOUND_BUFFER.Load("sounds/boss.mp3");

	SOUND_MGR.SetVolumeBGM(100.f);

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

	uiTitle3 = new TextGo("ToGame");
	uiTitle3->Set(RES_MGR_FONT.Get("font/NotoSansKR-Regular.otf"), "Press Enter to Game", 70, sf::Color::White);
	uiTitle3->SetOrigin(Origins::MC);
	uiTitle3->SetPosition({ GetViewCenter().x, GetViewCenter().y + 280 });
	AddGo(uiTitle3);

	uiTitle4 = new TextGo("Exit");
	uiTitle4->Set(RES_MGR_FONT.Get("font/NotoSansKR-Regular.otf"), "Press ESC to Exit", 40, sf::Color::White);
	uiTitle4->SetOrigin(Origins::MC);
	uiTitle4->SetPosition({ GetViewCenter().x - 480, GetViewCenter().y - 350 });
	AddGo(uiTitle4);
	Scene::Init();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::F1)) 
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneAnimatorEditer);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		SCENE_MGR.ChangeScene(SceneIds::SceneTilemapEditor);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.GetScene(SceneIds::SceneGame)->Reset();
		FRAMEWORK.SetTimeScale(1.f);
		SCENE_MGR.ChangeScene(SceneIds::SceneGame);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		FRAMEWORK.GetWindow().close();
	}
}

void SceneTitle::Enter()
{
	Scene::Enter();
	SCENE_MGR.TitleBgm();
}

void SceneTitle::Draw(sf::RenderWindow& window)
{

	Scene::Draw(window);
}
