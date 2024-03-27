#pragma once
#include "Enemy.h"
class Mutalisk : public Enemy
{
protected:
	Mutalisk(const Mutalisk&) = delete;
	Mutalisk(Mutalisk&&) = delete;
	Mutalisk& operator=(const Mutalisk&) = delete;
	Mutalisk& operator=(Mutalisk&&) = delete;

public:
	Mutalisk(const std::string& name = "", const std::string& animationName = "");
	~Mutalisk() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

