#include "pch.h"
#include "TileEditor.h"
#include "TileSet.h"
#include "SpriteGo.h"
#include "Scenes/SceneTilemapEditor.h"
#include "Crosshair.h"
#include "UIGo.h"
#include <Windows.h>
#include <commdlg.h> 
#include "rapidjson/document.h"

using namespace rapidjson;

TileEditor::TileEditor(const std::string& name) : UIGo(name), font(RES_MGR_FONT.Get("font/NotoSansKR-Regular.otf"))
{}

void TileEditor::Init()
{
	sceneTilemapEditor = dynamic_cast<SceneTilemapEditor*>(SCENE_MGR.GetScene(SceneIds::SceneTilemapEditor));
	tileSet = sceneTilemapEditor->GetTileSet();
	NewSpriteGo("tilemapSheet", "graphics/Tile/Tilemap_Sheet.png");
	sprites["tilemapSheet"]->SetPosition({ 50,50 });
	sprites["tilemapSheet"]->sortLayer = 1;

	for (int i = 0; i < 9; ++i) {
		typeselectBox[i].setSize({ 32,32 });
		typeselectBox[i].setPosition(50.f, 50.f + 32.f * i);
	}

	selectBox.setSize({ 32,32 });
	selectBox.setPosition(50.f, 50.f);
	selectBox.setFillColor(sf::Color::Transparent);
	selectBox.setOutlineThickness(2.f);
	selectBox.setOutlineColor(sf::Color::White);

	NewSpriteGo("currentSelectedBox", "graphics/Tile/Tilemap_Sheet.png");
	sprites["currentSelectedBox"]->SetPosition({ 50,50 });
	sprites["currentSelectedBox"]->sortLayer = 1;

	UiInit();
	ObjectsSort();

}

void TileEditor::Update(float dt)
{
	GameObject::Update(dt);


	screenPos = SCENE_MGR.GetCurrentScene()->UiToScreen((sf::Vector2f)mouse->GetPosition());
	worldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(screenPos);

	//std::cout << worldPos.x << " " << worldPos.y << std::endl;
	isMouseOutsideAllBoxes = true; // 타일박스에 커서 올라가있는것 판단

	for (int i = 0; i < 9; ++i) {
		if (typeselectBox[i].getGlobalBounds().contains(mouse->GetPosition()))
		{
			isMouseOutsideAllBoxes = false;
			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
			{
				selectBox.setPosition(typeselectBox[i].getPosition());
				currentType = (TileType)i;
			}
		}
	}
	sprites["currentSelectedBox"]->GetSprite()->setTextureRect({ 0,0,32,32 * (int)currentType });



	if (isMouseOutsideAllBoxes)
	{
		if (InputMgr::GetMouseButton(sf::Mouse::Left))
		{
			tileSet->SetTileType(worldPos.x / 32 , worldPos.y / 32 , currentType);
		}
	}

	//마우스로 뷰 이동

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Middle))
	{
		lastMouseWorldPos = worldPos; // 현재 마우스 위치를 저장합니다.
	}

	// 마우스 휠이 눌린 상태 유지 전에 delta랑 위치가 같지 않을때만
	if (InputMgr::GetMouseButton(sf::Mouse::Middle) &&
		delta != lastMouseWorldPos - worldPos)
	{
		delta = lastMouseWorldPos - worldPos; // 이동량.

		sceneTilemapEditor->GetWorldView().move(delta);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::F1))
	{
		tileSet->SaveTileMap("tilejson/");
		std::cout << "SAVE" << std::endl;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::F2))
	{
		TCHAR str_currentPath[1024];
		GetCurrentDirectory(1024, str_currentPath);
		tileSet->LoadTileMap(convertToRelativePath(OpenFile()), 0.5f);
		tileSet->VaSet();
		std::cout << "LOAD" << std::endl;
	}
}

void TileEditor::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	UiDraw(window);
	window.draw(selectBox);
}

std::wstring TileEditor::OpenFile(const wchar_t* filter, HWND owner)
{
	OPENFILENAMEW ofn;
	wchar_t fileName[MAX_PATH] = L"";
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"";

	if (GetOpenFileNameW(&ofn))
		return fileName;

	return Utils::CP949ToWString(tilePath);
}

std::string TileEditor::convertToRelativePath(const std::wstring& absolutePathW)
{
	std::string absolutePath = Utils::WSTRINGToString(absolutePathW);

	return absolutePath;
}
