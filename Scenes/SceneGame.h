#pragma once
#include "Scene.h"
#include "ShapeGo.h"

class Hydralisk;
class Dragoon;
class Ghost;

class TileSet;
class Interface;

class SceneGame : public Scene
{
public:

	enum class MessageType
	{
		NONE = -1,
		NotEnoughMinerals,
		count,
	};

protected:
	TileSet* tileSet = nullptr;

	Interface* mainInterface = nullptr;
	ShapeGo<sf::RectangleShape>* leftFiller;
	ShapeGo<sf::RectangleShape>* rightFiller;

	Crosshair* mouse = nullptr;
	sf::Vector2i screenPos;
	sf::Vector2f worldPos;
	sf::Vector2i tilePos;
	sf::Vector2f lastMouseWorldPos;
	sf::Vector2f delta;
	
	std::list<GameObject*> HydraliskList;
	std::list<GameObject*> DragoonList;
	std::list<GameObject*> GhostList;

	int hydraliskUpgrade = 0;
	int dragoonUpgrade = 0;
	int ghostUpgrade = 0;

	int mineral = 0;
	int gas = 0;

public:

	SceneGame(SceneIds id);
	~SceneGame() override = default;

	SceneGame(const SceneGame&) = delete;
	SceneGame(SceneGame&&) = delete;
	SceneGame& operator=(const SceneGame&) = delete;
	SceneGame& operator=(SceneGame&&) = delete;

	const std::list<GameObject*>& GetHydraliskList() const { return HydraliskList; }
	const std::list<GameObject*>& GetDragoonList() const { return DragoonList; }
	const std::list<GameObject*>& GetGhostList() const { return GhostList; }

	void SetHydraliskUpgrade(int h) { hydraliskUpgrade = h; }
	void SetDragoonUpgrade(int d) { dragoonUpgrade = d; }
	void SetGhostUpgrade(int g) { ghostUpgrade = g; }
	const int GetHydraliskUpgrade() const { return hydraliskUpgrade; }
	const int GetDragoonUpgrade() const { return dragoonUpgrade; }
	const int GetGhostUpgrade() const { return ghostUpgrade; }

	void SetMineral(int m) { mineral = m; }
	const int GetMineral() const { return mineral; }

	void message(MessageType m);
	void UpgradeUpdate();

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

