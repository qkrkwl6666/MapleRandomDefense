#pragma once
#include "SCUnit.h"
class Hydralisk : public SCUnit
{
protected:

public:
	Hydralisk(const std::string& name = "");
	~Hydralisk() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

