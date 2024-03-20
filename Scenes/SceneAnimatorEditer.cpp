#include "pch.h"
#include "SceneAnimatorEditer.h"
#include "UIAnimatorEditer.h"

SceneAnimatorEditer::SceneAnimatorEditer(SceneIds id)
	:Scene(id)
{

}

void SceneAnimatorEditer::Init()
{
	uiAnimatorEditer = new UIAnimatorEditer();

	AddGo(uiAnimatorEditer, Scene::Ui);

	Scene::Init();
}

void SceneAnimatorEditer::Update(float dt)
{
	Scene::Update(dt);
}

void SceneAnimatorEditer::Enter()
{
	Scene::Enter();
}

void SceneAnimatorEditer::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
