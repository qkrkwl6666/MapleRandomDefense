#pragma once
#include "SpriteGo.h"
class SceneGame;

class Building : public SpriteGo
{
public:

	enum class Races
	{
		NONE = -1,
		Zerg,
		Protoss,
		Terran,
		count,
	};

	enum class BuildingType
	{
		NONE,
		UPGRADE,
		SELL,
	};

protected:
	BuildingType type = BuildingType::NONE;
	SceneGame* sceneGame = nullptr;

	bool isSelect = false;
	std::shared_ptr<SpriteGo> isSelectSprite;

public:
	Building(const std::string& name = "");
	~Building() = default;

	void Init() override;
	void Reset() override;
	void Draw(sf::RenderWindow& window) override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	const BuildingType& GetBuildingType() { return type; }

	void SetSelect(bool isSelect);
	const bool& GetSelect() { return isSelect; }
};

