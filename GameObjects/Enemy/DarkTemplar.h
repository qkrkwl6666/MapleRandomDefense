#pragma once
#include "Enemy.h"
class DarkTemplar : public Enemy
{
protected:
	DarkTemplar(const DarkTemplar&) = delete;
	DarkTemplar(DarkTemplar&&) = delete;
	DarkTemplar& operator=(const DarkTemplar&) = delete;
	DarkTemplar& operator=(DarkTemplar&&) = delete;

public:
	DarkTemplar(const std::string& name = "", const std::string& animationName = "");
	~DarkTemplar() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

