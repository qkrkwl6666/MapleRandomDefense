#pragma once
#include "SpriteAnimatorGo.h"
#include "TileSet.h"
#include <cstdint>

class SceneGame;
class SpriteGo;


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

	// Astar 
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

protected:

	SceneGame* sceneGame = nullptr;

	std::shared_ptr<SpriteGo> isSelectSprite;
	bool isSelect = false;
	sf::Vector2f direction;

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
	///////////////////////// 애니메이션 관련

	Type type = Type::NONE;
	Rarity rarity = Rarity::NONE;
	float Damage = 3.f;
	float attackRange = 3.f;
	int UpgradeCount = 0;
	int sellingValue = 0; // 판매 가격
	bool sellable = true; // 전설 신화 태초만 false

// 길찾기
protected:
	struct Node
	{
		Node(int f, int g, sf::Vector2i pos) :
			f(f), g(g), pos(pos) {}
		// 현재 타일 인덱스 worldPos / 32

		sf::Vector2i pos; 

		int f; // f = g + h;
		int g; // g = 시작점 부터 현재 cost
		// h = 목적지 인덱스 부터 현재 인덱스 빼기
		// goal[x][y] - pos[x][y]; 

		// 우선순위 큐는 기본적으로 가장 큰 원소를 먼저 pop하기 때문에 반대로 정의
		bool operator<(const Node& other) const
		{
			return f > other.f; 
		}
	};

	// ******************Astar******************
	std::vector<sf::Vector2i> front =
	{
		{0 , -1}, // TOP
		{1 , 0}, // RIGHT
		{0 , 1}, // DOWN
		{-1 , 0}, // LEFT
		// 대각선
		{1 , -1}, // RIGHT_TOP
		{1 , 1}, // RIGHT_DOWN
		{-1 , 1}, // LEFT_DOWN
		{-1 , -1}, // LEFT_TOP
	};

	std::vector<int> cost =
	{
		10,
		10,
		10,
		10,
		14, // 대각선
		14,
		14,
		14,
	};
	
	// 맵 크기
	int size = 256;	

	void Astar(sf::Vector2f dest);

	bool CanGo(sf::Vector2i pos);

	// 길찾기 경로
	std::vector<sf::Vector2i> path;
	int pathIndex = 0;
	sf::Vector2i pos;

	bool isAster = false;

	float moveSpeed = 100.f;

	
public:
	SCUnit(const std::string& name = "" , 
		const std::string& animationName = "");
	~SCUnit() override;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SellThis();

	const Angle& GetCurrentAngle() const { return currentAngle; }
	void SetStatus(Status status);
	void SetUpgrade(int u) { UpgradeCount = u; }

	const Rarity& GetRarity() const { return rarity; }

	void SetSelect(bool isSelect);



};

