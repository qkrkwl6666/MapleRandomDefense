#pragma once
#include "Enemy.h"
class Zealot : public Enemy
{
protected:
	Zealot(const Zealot&) = delete;
	Zealot(Zealot&&) = delete;
	Zealot& operator=(const Zealot&) = delete;
	Zealot& operator=(Zealot&&) = delete;

public:
	Zealot(const std::string& name = "", const std::string& animationName = "");
	~Zealot() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

