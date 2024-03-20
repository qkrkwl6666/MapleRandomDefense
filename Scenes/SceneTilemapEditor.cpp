#include "pch.h"
#include "SceneTilemapEditor.h"
#include "SpriteGo.h"
#include "TileEditor.h"
#include "TileSet.h"

SceneTilemapEditor::SceneTilemapEditor(SceneIds id) : Scene(id)
{
}

void SceneTilemapEditor::Init()
{
	tileSet = new TileSet();
	AddGo(tileSet, Scene::World);
	tileEditor = new TileEditor();
	AddGo(tileEditor, Scene::Ui);

	Scene::Init();
}

void SceneTilemapEditor::Update(float dt)
{
	Scene::Update(dt);
}

void SceneTilemapEditor::Enter()
{
	Scene::Enter();
	sf::Font& font = RES_MGR_FONT.Get("fonts/NotoSansKR-Regular.otf");

}

void SceneTilemapEditor::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
