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
		sf::RectangleShape shape;
		sf::Texture texture;
		TileType type;

		Tile() : type(TileType::WATER) 
		{}

		Tile(int x, int y, int type)
		{
			shape.setPosition(x * 32, y * 32);
			shape.setSize({32,32});
			shape.setFillColor(sf::Color::Black); // ����
			shape.setOutlineThickness(0.6f);
			shape.setOutlineColor(sf::Color::White); // �⺻ WALL ����
			this->type = (TileType)type;
		}
	};

protected:
	std::vector<std::vector<Tile>> tiles;
	
public:
	TileSet() : tiles(256, std::vector<Tile>(256)) {}
	~TileSet() = default;

	TileSet(const TileSet&) = delete;
	TileSet(TileSet&&) = delete;
	TileSet& operator=(const TileSet&) = delete;
	TileSet& operator=(TileSet&&) = delete;

	void Draw(sf::RenderWindow& window) override;


	void SetTileTexture(int y, int x, const TileType& type);

	const std::vector<std::vector<Tile>>& GetTiles()
	{
		return tiles;
	}

	void SaveTileMap(const std::string& filePath);
	void LoadTileMap(const std::string& filePath, const float setOutlineThickness);

};

