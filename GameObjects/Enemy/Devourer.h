#pragma once
#include "Enemy.h"
class Devourer : public Enemy
{
protected:
	Devourer(const Devourer&) = delete;
	Devourer(Devourer&&) = delete;
	Devourer& operator=(const Devourer&) = delete;
	Devourer& operator=(Devourer&&) = delete;

public:
	Devourer(const std::string& name = "", const std::string& animationName = "");
	~Devourer() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

