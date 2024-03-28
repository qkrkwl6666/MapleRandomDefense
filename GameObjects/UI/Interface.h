#pragma once
#include "UIGo.h"
#include "SCUnit.h"
#include "ShapeGo.h"
#include "RichText.h"

class SCUnit;
class Building;
class Spawner;

class Interface : public UIGo
{
public:
	enum class UIStatus
	{
		NONE = -1,
		Upgrade,
		SellUnitSellect,
		SellRaritySellect,
		Unit,
		Enemy,
		COUNT,
	};


protected:
	Interface(const Interface&) = delete;
	Interface(Interface&&) = delete;
	Interface& operator=(const Interface&) = delete;
	Interface& operator=(Interface&&) = delete;
	Spawner* enemySpawer = nullptr;
	UIStatus uiStatus = UIStatus::NONE;
	SCUnit::Type uiUnitType = SCUnit::Type::NONE;
	GameObject* UItarget = nullptr;
	ShapeGo<sf::RectangleShape>* selectBox;
	sf::Vector2f selectStartPos;
	bool isSelecting = false;
	bool noUnits = true;
	bool mouseOnUi = false;
	bool onWarframeName = false;
	bool onDamageInfo = false;
	sfe::RichText warframeName;
	int rarity[5] = {};
	std::list<SCUnit*> isSelectList;
	
	sf::Vector2f worldMousePos;
	sf::Vector2i screenMousePos;
	std::unordered_map<std::string, Building*> buildings;
	std::wstring stageName;
	float uiTimer = 0.f;
	int gameTimer = 30;
	int min = 0;
	std::string uiTimerString = "00:30";

	int currentStage = 0;
	float currentStageTimer = 100.f;
	float currentStageDuration = 12.f;


public:
	Interface(const std::string& name = "");
	~Interface() override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void UpdateUpgrade(float dt);
	void UpdateSellUnitSellect(float dt);
	void UpdateSellRaritySellect(float dt);
	void UpdateUnit(float dt);
	void UpdateEnemy(float dt);
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetActiveUpgrade(bool active);
	void SetActiveSell(bool active);
	void SetActiveSellInfo(bool active , SCUnit::Type t);

	void HydraliskSellUpdate();
	void DragoonSellUpdate();
	void GhostSellUpdate();

	void SetSellUiTexture(const std::string& typeName , const std::string& rarityName, const int rarityIndex);
	void Upgrade();

	void SetWarframeView(bool active);
	void SetWeaponInfoView(bool active);
	void OnUpgradeInfoView(SCUnit::Type t);
	void OffUpgradeInfoView();

	const int GetStage() const {return currentStage;}
	void SetStage(int stage) {currentStage = stage;}
	void SetUiTarget(GameObject* t) { UItarget = t; }
	const GameObject* GetUiTarget() const { return UItarget; }
	bool GetMouseOnUi() { return mouseOnUi; }
	void ClearText(bool active);
	void LoseText(bool active);
};

