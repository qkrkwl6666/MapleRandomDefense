#pragma once
#include "Enemy.h"
class Zergling : public Enemy
{
protected:

public:
	Zergling(const std::string& name = "", const std::string& animationName = "");
	~Zergling() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

