#pragma once
#include "Enemy.h"
class Ultralisk : public Enemy
{
protected:
	Ultralisk(const Ultralisk&) = delete;
	Ultralisk(Ultralisk&&) = delete;
	Ultralisk& operator=(const Ultralisk&) = delete;
	Ultralisk& operator=(Ultralisk&&) = delete;

public:
	Ultralisk(const std::string& name = "", const std::string& animationName = "");
	~Ultralisk() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

