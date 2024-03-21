#pragma once
#include "Scene.h"
#include "ShapeGo.h"

class TileSet;

class SceneGame : public Scene
{
protected:
	TileSet* tileSet = nullptr;

	ShapeGo<sf::RectangleShape>* leftFiller;
	ShapeGo<sf::RectangleShape>* rightFiller;

	Crosshair* mouse = nullptr;
	sf::Vector2i screenPos;
	sf::Vector2f worldPos;
	sf::Vector2i tilePos;
	sf::Vector2f lastMouseWorldPos;
	sf::Vector2f delta;

public:



	SceneGame(SceneIds id);
	~SceneGame() override = default;

	SceneGame(const SceneGame&) = delete;
	SceneGame(SceneGame&&) = delete;
	SceneGame& operator=(const SceneGame&) = delete;
	SceneGame& operator=(SceneGame&&) = delete;

	void Init() override;
	void Release() override;
	void Reset() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void DebugUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

