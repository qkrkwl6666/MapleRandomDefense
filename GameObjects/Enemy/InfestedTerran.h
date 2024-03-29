#pragma once
#include "Enemy.h"
class InfestedTerran : public Enemy
{
protected:
	InfestedTerran(const InfestedTerran&) = delete;
	InfestedTerran(InfestedTerran&&) = delete;
	InfestedTerran& operator=(const InfestedTerran&) = delete;
	InfestedTerran& operator=(InfestedTerran&&) = delete;

public:
	InfestedTerran(const std::string& name = "", const std::string& animationName = "");
	~InfestedTerran() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

