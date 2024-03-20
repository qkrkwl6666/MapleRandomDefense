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
			shape.setFillColor(sf::Color::White); // ����
			shape.setOutlineThickness(0.6f);
			shape.setOutlineColor(sf::Color::White); // �⺻ WALL ����
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

