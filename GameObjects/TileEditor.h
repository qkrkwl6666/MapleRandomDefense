#pragma once
#include "GameObject.h"
#include "TileSet.h"'
#include "UIGo.h"
#include <Windows.h> // TODO �ϴ� �ӽ÷� ���

class TileSet;
class SceneTilemapEditor;

class TileEditor :
	public UIGo
{

protected:
    sf::RectangleShape selectBox;
    sf::RectangleShape typeselectBox[9];
    TileSet::TileType currentSelectedType;
 
    SceneTilemapEditor* sceneTilemapEditor;
    TileSet* tileSet;

	sf::VertexArray va;

    sf::Vector2i screenPos;
    sf::Vector2f worldPos;
    sf::Vector2i tilePos;
    sf::Vector2f lastMouseWorldPos;
    sf::Vector2f delta;

	sf::Font& font;

    bool isMouseOutsideAllBoxes = true;
    TileSet::TileType currentType = TileSet::TileType::WALL;
	std::vector<std::vector<TileSet::Tile>> tilesInit;
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


	void SetCheck(bool c);
	void HandleMouseSelection(); // UI ���콺 ����
	void TileMouseSelection(bool isRemove = false); // Ÿ�� ���콺 ���� �̺�Ʈ
	void TileTypeMouseSelection();
	void TileSetTexture(const std::string& filePath);

	void typeTextSet();
	void typeTextDelete();

	std::wstring OpenFile(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL);

	void SetActiveTypeUI(bool active);
	bool GetActiveTypeUI() const { return isMouseOutsideAllBoxes; }

	// ���� ��� ���� wstring to string
	std::string convertToRelativePath(const std::wstring& absolutePathW);


};

