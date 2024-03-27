#pragma once
#include "Enemy.h"

class Guardian : public Enemy
{
protected:
	Guardian(const Guardian&) = delete;
	Guardian(Guardian&&) = delete;
	Guardian& operator=(const Guardian&) = delete;
	Guardian& operator=(Guardian&&) = delete;

public:
	Guardian(const std::string& name = "", const std::string& animationName = "");
	~Guardian() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

