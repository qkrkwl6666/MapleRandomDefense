#pragma once
#include "GameObject.h"
#include "UIGo.h"
#include <Windows.h> // TODO 일단 임시로 사용

class TileSet;
class SceneTilemapEditor;

class TileEditor :
	public UIGo
{
protected:
    sf::RectangleShape selectBox;
    sf::RectangleShape typeselectBox[9];
    TileType currentSelectedType;
 
    SceneTilemapEditor* sceneTilemapEditor;
 
	sf::VertexArray va;

    sf::Vector2i screenPos;
    sf::Vector2f worldPos;
    sf::Vector2i tilePos;
    sf::Vector2f lastMouseWorldPos;
    sf::Vector2f delta;

	sf::Font& font;

    bool isMouseOutsideAllBoxes = true;
    TileType currentType = TileType::WALL;

	TileSet* tileSet = nullptr;

	std::string tilePath = "tileset/Spr_Stage1_Tileset_1.png";
	//TO-DO 맵 저장 파일 하나 만들기


public:

	TileEditor(const std::string& name = "");
	~TileEditor() = default;
	TileEditor(const TileEditor&) = delete;
	TileEditor(TileEditor&&) = delete;
	TileEditor& operator=(const TileEditor&) = delete;
	TileEditor& operator=(TileEditor&&) = delete;

	void Init() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	std::wstring OpenFile(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL);

	// 절대 경로 제거 wstring to string
	std::string convertToRelativePath(const std::wstring& absolutePathW);


};

