#pragma once
#include "SpriteAnimatorGo.h"

class Enemy;

class DragoonBullet :
    public SpriteAnimatorGo
{
protected:
	Enemy* target = nullptr;
	float speed = 300;
	int damage;
	sf::Vector2f direction;
	sf::Vector2f targetPos;
	std::string animationName = "";

public:
	DragoonBullet(const std::string& name = "",
		const std::string& animationName = "");
	~DragoonBullet() override;

	void Init(Enemy* t, int d);
	void Update(float dt) override;

};

