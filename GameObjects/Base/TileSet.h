#pragma once
#include "GameObject.h"

class TileSet : public GameObject
{
public:

	struct Tile
	{
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
	wchar_t currentDirectory[256];

protected:

	sf::VertexArray va;
	std::vector<std::vector<Tile>> tiles;

public:

	TileSet();
	~TileSet() = default;

	TileSet(const TileSet&) = delete;
	TileSet(TileSet&&) = delete;
	TileSet& operator=(const TileSet&) = delete;
	TileSet& operator=(TileSet&&) = delete;

	void Init() override;

	void VaSet();
	void SetTileType(int x, int y, TileType type);

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;


	void SaveTileMap(const std::string& filePath);
	void LoadTileMap(const std::string& filePath, const float setOutlineThickness);

	std::vector<std::vector<Tile>>& GetTiles() { return tiles; }
};

