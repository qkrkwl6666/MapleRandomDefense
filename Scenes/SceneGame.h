#pragma once
#include "Scene.h"
#include "ShapeGo.h"
#include "SCUnit.h"
#include "TextGo.h"
#include "RichText.h"


class Hydralisk;
class Dragoon;
class Ghost;
class Enemy;
class TextGo;
class Civilian;

class TileSet;
class Interface;
class Building;
class Spawner;
class DeveloperMode;

class SceneGame : public Scene
{
public:

	enum class MessageType
	{
		NONE = -1,
		BuyUnit,
		NotEnoughMinerals,
		NoMoreSpace,
		SellUnit,
		Warning,
		count,
	};

	struct SystemMessage
	{
		SystemMessage()
		{
			systemMessage = new sfe::RichText();
		}
		~SystemMessage()
		{
		}
		sfe::RichText* systemMessage;
		float messageTimer = 0;
		float messageInterval = 12.f;
		void Update(float dt)
		{
			messageTimer += dt;
		}
	};
	// Å×½ºÆ®

protected:
	TileSet* tileSet = nullptr;
	Spawner* spawner = nullptr;
	DeveloperMode* developerMode = nullptr;

	std::list<SystemMessage> messageContainer;
	Interface* mainInterface = nullptr;
	ShapeGo<sf::RectangleShape>* leftFiller;
	ShapeGo<sf::RectangleShape>* rightFiller;
	sf::RectangleShape UnitSummonLocation;
	sf::Vector2f basePosition;
	sf::Vector2f offset{ 16,16 };
	bool SummonStuck = false;
	Civilian* civilian = nullptr;
	Crosshair* mouse = nullptr;
	sf::Vector2i screenPos;
	sf::Vector2f worldPos;
	sf::Vector2i tilePos;
	sf::Vector2f lastMouseWorldPos;
	sf::Vector2f delta;
	
	std::list<SCUnit*> HydraliskList;
	std::list<SCUnit*> DragoonList;
	std::list<SCUnit*> GhostList;

	std::list<SCUnit*> AllUnitList;

	std::list<Enemy*>* EnemyList;

	// ºôµù 
	std::unordered_map<std::string, Building*> buildings;

	int hydraliskUpgrade = 0;
	int dragoonUpgrade = 0;
	int ghostUpgrade = 0;

	int mineral = 0;
	TextGo* mineralText = nullptr;
	int gas = 0;
	TextGo* gasText = nullptr;

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

	const std::list<SCUnit*>& GetAllUnitList() const { return AllUnitList; }

	std::unordered_map<std::string, Building*>& GetBuildings() { return buildings; }

	void SetHydraliskUpgrade(int h) { hydraliskUpgrade = h; }
	void SetDragoonUpgrade(int d) { dragoonUpgrade = d; }
	void SetGhostUpgrade(int g) { ghostUpgrade = g; }
	const int GetHydraliskUpgrade() const { return hydraliskUpgrade; }
	const int GetDragoonUpgrade() const { return dragoonUpgrade; }
	const int GetGhostUpgrade() const { return ghostUpgrade; }

	void SellUnit(SCUnit::Type t, SCUnit::Rarity r);
	Enemy* FindEnemy(sf::Vector2f pos, float range);

	void SetMineral(int m) { mineral = m; }
	const int GetMineral() const { return mineral; }

	void message(MessageType m);
	void message(MessageType m, SCUnit::Type t, SCUnit::Rarity r);
	void MessageUpdate(float dt);
	void MessageOpen();
	void MessageClose();

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
	sf::Vector2i GetScreenMousePos() { return screenPos; }
	TileSet* GetTileSet() { return tileSet; }

	Interface* GetInterface() { return mainInterface; }
	std::list<Enemy*>* GetEnemyList() { return EnemyList; }
	Spawner* GetSpawner() { return spawner; }
	void GasUp() { gas++; }

	DeveloperMode* GetDeveloperMode() { return developerMode; }

	void BuyUnit();

	void BuyUnit(int d);
};

