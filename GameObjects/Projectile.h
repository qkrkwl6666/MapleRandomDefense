#pragma once
#include "SpriteAnimatorGo.h"
class Projectile : public SpriteAnimatorGo
{
protected:

public:
	Projectile(const std::string& name = "");
	~Projectile() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void Update(float dt, Angle angle);
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	std::shared_ptr<Animator> GetAnimator() { return animator; }
};

