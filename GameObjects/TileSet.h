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
		sf::Texture texture;
		TileType type;
		int index = 0;
		Tile() : type(TileType::WALL) 
		{}
		Tile(TileType type, int i)
		{
			this->type = type;
			index = i;
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
	void SetTileTexture(int x, int y, const TileType& type);

	int count;

	const std::vector<std::vector<Tile>>& GetTiles()
	{
		return tiles;
	}

	void SaveTileMap(const std::string& filePath);
	void LoadTileMap(const std::string& filePath, const float setOutlineThickness);

};

