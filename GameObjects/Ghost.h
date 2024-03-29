#pragma once
#include "SCUnit.h"
class Ghost : public SCUnit
{
protected:

public:
	Ghost(const std::string& name = "", SCUnit::Rarity r = SCUnit::Rarity::NONE);
	~Ghost() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

