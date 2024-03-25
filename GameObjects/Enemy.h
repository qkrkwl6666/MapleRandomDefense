#pragma once
#include "SCUnit.h"


class SceneGame;
class SpriteGo;

class Enemy : public SCUnit
{
public:
	enum class ArmorType
	{
		NONE = -1,
		SMALL,
		MEDIUM,
		LARGE,
		COUNT,
	};

protected:

	float Hp = 10.f;
	float speed = 100.f;
	ArmorType armor = ArmorType::NONE;

public:
	Enemy(const std::string& name = "", const std::string & animationName = "");
	~Enemy() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

