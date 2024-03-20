#include "pch.h"
#include "SceneTilemapEditor.h"
#include "SpriteGo.h"

SceneTilemapEditor::SceneTilemapEditor(SceneIds id) :Scene(id)
{
}

void SceneTilemapEditor::Init()
{
	tilemapSheet = new SpriteGo("tilemapSheet");
	tilemapSheet->SetTexture("graphics/Tile/Tilemap_Sheet.png");
	tilemapSheet->SetPosition({ 50,50 });
	AddGo(tilemapSheet);
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
