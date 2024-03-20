#include "pch.h"
#include "SceneTilemapEditor.h"
#include "SpriteGo.h"

SceneTilemapEditor::SceneTilemapEditor(SceneIds id) :Scene(id)
{
}

void SceneTilemapEditor::Init()
{
	Scene::Init();
}

void SceneTilemapEditor::Update(float dt)
{
	Scene::Update(dt);
}

void SceneTilemapEditor::Enter()
{
	Scene::Enter();

}

void SceneTilemapEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
