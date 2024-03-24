#pragma once
#include "SpriteAnimatorGo.h"


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

protected:

	SceneGame* sceneGame = nullptr;

	std::shared_ptr<SpriteGo> isSelectSprite;
	bool isSelect = false;
	sf::Vector2f direction;

	Angle currentAngle = Angle::TOP;
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

	//////////////////

	float Hp = 10.f;
	float speed = 100.f;
	ArmorType armor = ArmorType::NONE;
	int Stage = 1;

public:
	Enemy(const std::string& name = "", const std::string & animationName = "");
	~Enemy() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

