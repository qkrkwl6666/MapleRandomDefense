#pragma once
#include "GameObject.h"
#include "TileSet.h"
#include <Windows.h> // TODO �ϴ� �ӽ÷� ���

class TileSet;
class SceneTilemapEditor;

class TileEditor :
    public GameObject
{

protected:
    sf::RectangleShape selectBox;
    sf::RectangleShape typeselectBox;
    TileSet::TileType selectedType;
    

    SpriteGo* tilemapSheet = nullptr;
    SceneTilemapEditor* sceneTileEditor;
    TileSet* tileSet;

    sf::Vector2i screenPos;
    sf::Vector2f worldPos;
    sf::Vector2i tilePos;
    sf::Vector2f lastMouseWorldPos;
    sf::Vector2f delta;

	sf::Font& font;

    bool isTypeUI = false;
    TileSet::TileType currentType = TileSet::TileType::WATER;
public:

	TileEditor(const std::string& name = "");
	~TileEditor() = default;
	TileEditor(const TileEditor&) = delete;
	TileEditor(TileEditor&&) = delete;
	TileEditor& operator=(const TileEditor&) = delete;
	TileEditor& operator=(TileEditor&&) = delete;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;

	void SetCheck(bool c);
	void Draw(sf::RenderWindow& window) override;
	void HandleMouseSelection(); // UI ���콺 ����
	void TileMouseSelection(bool isRemove = false); // Ÿ�� ���콺 ���� �̺�Ʈ
	void TileTypeMouseSelection();
	void TileSetTexture(const std::string& filePath);

	void typeTextSet();
	void typeTextDelete();

	std::wstring OpenFile(const wchar_t* filter = L"All Files (*.*)\0*.*\0", HWND owner = NULL);

	void SetActiveTypeUI(bool active);
	bool GetActiveTypeUI() const { return isTypeUI; }

	// ���� ��� ���� wstring to string
	std::string convertToRelativePath(const std::wstring& absolutePathW);


};

