#pragma once
#include "Enemy.h"
class Overlord : public Enemy
{
protected:
	Overlord(const Overlord&) = delete;
	Overlord(Overlord&&) = delete;
	Overlord& operator=(const Overlord&) = delete;
	Overlord& operator=(Overlord&&) = delete;

public:
	Overlord(const std::string& name = "", const std::string& animationName = "");
	~Overlord() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

