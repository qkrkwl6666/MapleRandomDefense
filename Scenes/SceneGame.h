#pragma once
#include "Scene.h"
#include "ShapeGo.h"
#include "SCUnit.h"

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
		BuyUnit,
		NotEnoughMinerals,
		SellUnit,
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
	
	std::list<SCUnit*> HydraliskList;
	std::list<SCUnit*> DragoonList;
	std::list<SCUnit*> GhostList;

	int hydraliskUpgrade = 0;
	int dragoonUpgrade = 0;
	int ghostUpgrade = 0;

	int mineral = 0;
	int gas = 0;

	bool modeDeveloper = false;

public:

	SceneGame(SceneIds id);
	~SceneGame() override = default;

	SceneGame(const SceneGame&) = delete;
	SceneGame(SceneGame&&) = delete;
	SceneGame& operator=(const SceneGame&) = delete;
	SceneGame& operator=(SceneGame&&) = delete;

	const std::list<SCUnit*>& GetHydraliskList() const { return HydraliskList; }
	const std::list<SCUnit*>& GetDragoonList() const { return DragoonList; }
	const std::list<SCUnit*>& GetGhostList() const { return GhostList; }

	void SetHydraliskUpgrade(int h) { hydraliskUpgrade = h; }
	void SetDragoonUpgrade(int d) { dragoonUpgrade = d; }
	void SetGhostUpgrade(int g) { ghostUpgrade = g; }
	const int GetHydraliskUpgrade() const { return hydraliskUpgrade; }
	const int GetDragoonUpgrade() const { return dragoonUpgrade; }
	const int GetGhostUpgrade() const { return ghostUpgrade; }

	void SellUnit(SCUnit::Type t, SCUnit::Rarity r);

	void SetMineral(int m) { mineral = m; }
	const int GetMineral() const { return mineral; }

	void message(MessageType m);
	void message(MessageType m, SCUnit::Type t, SCUnit::Rarity r);
	void message(int i);

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

	sf::Vector2f GetWorldMousePos() { return worldPos; }

};

