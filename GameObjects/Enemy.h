#pragma once
#include "SCUnit.h"

class SceneGame;
class SpriteGo;

class Enemy : public SpriteAnimatorGo
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

	enum class Dir
	{
		TOP,
		RIGHT,
		DOWN,
		LEFT,
		RIGHT_TOP,
		RIGHT_DOWN,
		LEFT_DOWN,
		LEFT_TOP,
		COUNT,
	};

	std::vector<sf::Vector2f> front =
	{
		{0.f , -1.f}, // TOP
		{1.f , 0.f}, // RIGHT
		{0.f , 1.f}, // DOWN
		{-1.f , 0.f}, // LEFT
		// ´ë°¢¼±
		{1.f , -1.f}, // RIGHT_TOP
		{1.f , 1.f}, // RIGHT_DOWN
		{-1.f , 1.f}, // LEFT_DOWN
		{-1.f , -1.f}, // LEFT_TOP
	};

	std::unordered_map<int, Angle>angleMMap =
	{
		{0 , Angle::TOP},
		{1 , Angle::RIGHT},
		{2 , Angle::BOTTOM},
		{3 , Angle::RIGHT}, // FlipX

		{4 , Angle::TOP30}, // RIGHT_TOP
		{5 , Angle::BOTTOM30}, // RIGHT_DOWN
		{6 , Angle::BOTTOM30}, // LEFT_DOWN Flip
		{7 , Angle::TOP30}, // LEFT_TOP Flip
	};

	sf::Vector2f currentDirection;
	int Dir = (int)Dir::LEFT;
	float moveSpeed = 300.f;

	Angle currentAngle = Angle::RIGHT;

	float currentDegreeAngle = 0.f;
	std::string animationName = "";
	std::vector<float> AnimationAngle;
	std::unordered_map<float, Angle> angleMap =
	{
		{-90.f , Angle::TOP},
		{-67.5f , Angle::TOP15},
		{-45.f , Angle::TOP30},
		{-22.5f , Angle::TOP60},
		{0.f , Angle::RIGHT},
		{22.5f , Angle::BOTTOM60},
		{45.f , Angle::BOTTOM30},
		{67.5f , Angle::BOTTOM15},
		{90.f , Angle::BOTTOM},

		{-112.5f , Angle::TOP15},
		{-135.f , Angle::TOP30},
		{-157.5f , Angle::TOP60},
		{112.5f , Angle::BOTTOM15},
		{135.f , Angle::BOTTOM30},
		{157.5f , Angle::BOTTOM60},
		{180.f , Angle::RIGHT},
	};

protected:
	float hp = 10.f;

	ArmorType armor = ArmorType::NONE;

	std::vector<sf::Vector2f> changeDirPos;

public:
	Enemy(const std::string& name = "", const std::string & animationName = "");
	~Enemy() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnDamege(float damage);

	void Dead();

};

