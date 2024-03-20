#pragma once
#include "GameObject.h"

class SpriteGo;

class TileSet : public GameObject
{
public:
	enum class TileType
	{
		WALL, // 막히는 벽
		WATER, // 물
		SNOW,// 배치 가능한 땅
		GRASS, // 적 유닛 순회구역
		SPACE, //통과불가능한 격리구역
		ENEMYSPAWN, // 적 유닛 스폰구역
		TOWERSPAWN, // 타워 스폰구역
		SELECTOFF, // 선택 대기 구역
		SELECTON, // 선택 구역 (들어가면 선택)
	};

	struct Tile
	{
		// 타일 표시 테두리
		sf::VertexArray va;
		sf::RectangleShape shape;
		sf::Texture texture;
		TileType type;
		Tile() : type(TileType::WALL) 
		{}

		Tile(int x, int y, TileType type)
		{
			va.setPrimitiveType(sf::Quads);
			va.resize(4);
			va[0].position = sf::Vector2f(x * 32, y * 32);
			va[1].position = sf::Vector2f((x + 1) * 32, y * 32);
			va[2].position = sf::Vector2f((x + 1) * 32, (y + 1) * 32);
			va[3].position = sf::Vector2f(x * 32, (y + 1) * 32);

			shape.setPosition(x * 32, y * 32);
			shape.setSize({32,32});
			shape.setFillColor(sf::Color::White); // 배경색
			shape.setOutlineThickness(0.6f);
			shape.setOutlineColor(sf::Color::White); // 기본 WALL 색깔
			this->type = type;
		}
	};

protected:
	std::vector<std::vector<Tile>> tiles;
	sf::Texture tileTexture;
public:
	TileSet() : tiles(100, std::vector<Tile>(100)) {}
	~TileSet() = default;

	TileSet(const TileSet&) = delete;
	TileSet(TileSet&&) = delete;
	TileSet& operator=(const TileSet&) = delete;
	TileSet& operator=(TileSet&&) = delete;

	void Draw(sf::RenderWindow& window, int x, int y);

	void LoadTileTexture(const std::string& FilePath);
	void SetTileTexture(int y, int x, const TileType& type);

	int count;

	const std::vector<std::vector<Tile>>& GetTiles()
	{
		return tiles;
	}

	void SaveTileMap(const std::string& filePath);
	void LoadTileMap(const std::string& filePath, const float setOutlineThickness);

};

