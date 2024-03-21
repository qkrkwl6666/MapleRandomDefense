#pragma once
#include "GameObject.h"

class SpriteGo;

class TileSet : public GameObject
{
public:
	enum class TileType
	{
		WALL, // ������ ��
		WATER, // ��
		SNOW,// ��ġ ������ ��
		GRASS, // �� ���� ��ȸ����
		SPACE, //����Ұ����� �ݸ�����
		ENEMYSPAWN, // �� ���� ��������
		TOWERSPAWN, // Ÿ�� ��������
		SELECTOFF, // ���� ��� ����
		SELECTON, // ���� ���� (���� ����)
	};

	struct Tile
	{
		// Ÿ�� ǥ�� �׵θ�
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

