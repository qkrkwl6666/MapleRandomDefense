#pragma once
#include "SCUnit.h"
class Dragoon :
    public SCUnit
{
protected:

public:
	Dragoon(const std::string& name = "", SCUnit::Rarity r = SCUnit::Rarity::NONE);
	~Dragoon() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

