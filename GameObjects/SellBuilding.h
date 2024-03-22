#pragma once
#include "Building.h"
class SellBuilding :
    public Building
{
protected:

public:
	SellBuilding(const std::string& name = "");
	~SellBuilding() = default;

	void SellUnit();

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
};

