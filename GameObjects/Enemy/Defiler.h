#pragma once
#include "Enemy.h"
class Defiler : public Enemy
{
protected:
	Defiler(const Defiler&) = delete;
	Defiler(Defiler&&) = delete;
	Defiler& operator=(const Defiler&) = delete;
	Defiler& operator=(Defiler&&) = delete;

public:
	Defiler(const std::string& name = "", const std::string& animationName = "");
	~Defiler() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

