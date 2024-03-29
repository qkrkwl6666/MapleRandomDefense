#pragma once
#include "Enemy.h"
class TerranBoss : public Enemy
{
protected:
	TerranBoss(const TerranBoss&) = delete;
	TerranBoss(TerranBoss&&) = delete;
	TerranBoss& operator=(const TerranBoss&) = delete;
	TerranBoss& operator=(TerranBoss&&) = delete;

public:
	TerranBoss(const std::string& name = "", const std::string& animationName = "");
	~TerranBoss() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

