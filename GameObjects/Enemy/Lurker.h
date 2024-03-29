#pragma once
#include "Enemy.h"
class Lurker : public Enemy
{
protected:
	Lurker(const Lurker&) = delete;
	Lurker(Lurker&&) = delete;
	Lurker& operator=(const Lurker&) = delete;
	Lurker& operator=(Lurker&&) = delete;

public:
	Lurker(const std::string& name = "", const std::string& animationName = "");
	~Lurker() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

