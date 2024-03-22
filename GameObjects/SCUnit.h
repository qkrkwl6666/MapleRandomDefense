#pragma once
#include "SpriteAnimatorGo.h"

class SCUnit : public SpriteAnimatorGo
{
public:
	enum class Status
	{
		NONE = -1,
		IDLE,
		MOVE,
		ATTACK,
		COUNT,
	};

	enum class Type
	{
		NONE = -1,
		Hydralisk,
		Dragoon,
		Ghost,
		COUNT,
	};

	enum class Rarity
	{
		NONE = -1,
		Common,
		Rare,
		Ancient,
		Artifact,
		Saga,
		Legendary,
		Mythic,
		Primeval,
	};
protected:
	Angle currentAngle = Angle::TOP;
	float currentDegreeAngle = 0.f;
	Status currentStatus = Status::NONE;
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
	///////////////////////// 애니메이션 멤버 변수

	Type type = Type::NONE;
	Rarity rarity = Rarity::NONE;
	float Damage = 3.f;
	float attackRange = 3.f;
	int UpgradeCount = 0;
	int sellingValue = 0; // 판매가
	bool sellable = true; // 판매 가능 여부 - 전설 신화 태초만 false

public:
	SCUnit(const std::string& name = "" , 
		const std::string& animationName = "");
	~SCUnit() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	const Angle& GetCurrentAngle() const { return currentAngle; }
	void SetStatus(Status status);
	void SetUpgrade(int u) { UpgradeCount = u; }
	const Rarity& GetRarity() const { return rarity; }
};

