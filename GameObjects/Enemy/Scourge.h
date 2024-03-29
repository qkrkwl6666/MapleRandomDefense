#pragma once

#include "Enemy.h"

class Scourge : public Enemy
{
protected:
	Scourge(const Scourge&) = delete;
	Scourge(Scourge&&) = delete;
	Scourge& operator=(const Scourge&) = delete;
	Scourge& operator=(Scourge&&) = delete;

public:
	Scourge(const std::string& name = "", const std::string& animationName = "");
	~Scourge() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

