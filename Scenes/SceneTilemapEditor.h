#pragma once
#include "Scene.h"
class SpriteGo;
class TileEditor;
class TileSet;

class SceneTilemapEditor :
    public Scene
{
private:
	SceneTilemapEditor(const SceneTilemapEditor&) = delete;
	SceneTilemapEditor(SceneTilemapEditor&&) = delete;
	SceneTilemapEditor& operator=(const SceneTilemapEditor&) = delete;
	SceneTilemapEditor& operator=(SceneTilemapEditor&&) = delete;
	TileEditor* tileEditor = nullptr;
	TileSet* tileSet = nullptr;


public:
	SceneTilemapEditor(SceneIds id);
	~SceneTilemapEditor() override = default;

	TileSet* GetTileSet() { return tileSet; }
	void Init() override;
	void Update(float dt) override;
	void Enter() override;
	void Draw(sf::RenderWindow& window) override;
};

