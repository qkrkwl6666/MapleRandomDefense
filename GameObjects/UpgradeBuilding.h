#pragma once
#include "Building.h"

class UpgradeBuilding : public Building
{
protected:
	Building::Races races = Building::Races::NONE;

public:
	UpgradeBuilding(const std::string& name = "" , Building::Races r = Building::Races::NONE);
	~UpgradeBuilding() = default;

	void Upgrade();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;

	const Building::Races& GetRace() const { return races; }
};

