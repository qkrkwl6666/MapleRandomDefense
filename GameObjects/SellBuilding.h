#pragma once
#include "Building.h"
#include "SCUnit.h"

class SellBuilding : public Building
{
protected:


public:
	SellBuilding(const std::string& name = "");
	~SellBuilding() = default;

	void Sell(SCUnit::Type t , SCUnit::Rarity r);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
};

