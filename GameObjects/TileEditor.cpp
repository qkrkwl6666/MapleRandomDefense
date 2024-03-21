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

//
//void TileEditor::Init()
//{
//	//vertexArray
//
//	va.resize(4 * 256 * 256);
//	int index = 0;
//	std::list<int> list;
//	for (int i = 0; i < list.size(); i++)
//	{
//		va[i * 4 + 0].texCoords = { 0,0 };
//		va[i * 4 + 1].texCoords = { 32,0 };
//		va[i * 4 + 2].texCoords = { 32,32 };
//		va[i * 4 + 3].texCoords = { 0,32 };
//
//		va[i * 4 + 0].position = { 0,0 };
//		va[i * 4 + 1].position = { 32,0 };
//		va[i * 4 + 2].position = { 32,32 };
//		va[i * 4 + 3].position = { 0,32 };
//
//	}
//	//tiles.clear();
//	//	for (int i = 0; i < 256 * 256; i++)
//	//	{
//	//		tiles.pushback({ i, TileSet::TileType::WALL });
//	//	}
//
//
//		///위에까지가 초기화
//	//sf::RenderStates rs;
//	//rs.texture = &RES_MGR_TEXTURE.Get("graphics/Tile/Tilemap_Sheet.png");
//	//FRAMEWORK.GetWindow().draw(va, rs);
//	//
//
//	////변경
//	//
//	//va[tiles[][].index * 4 + 0].texCoords = { 0,0 };
//	//va[i * 4 + 1].texCoords = { 32,0 };
//	//va[i * 4 + 2].texCoords = { 32,32 };
//	//va[i * 4 + 3].texCoords = { 0,32 };
//
//
//
//	///기존 코드
//	sceneTilemapEditor = dynamic_cast<SceneTilemapEditor*>(SCENE_MGR.GetScene(SceneIds::SceneTilemapEditor));
//	tileSet = sceneTilemapEditor->GetTileSet();
//	tileSet->LoadTileTexture("graphics/Tile/Tilemap_Sheet.png");
//
//	tilesInit = tileSet->GetTiles();
//
//	for (size_t y = 0; y < tilesInit.size(); ++y)
//	{
//		for (size_t x = 0; x < tilesInit[y].size(); ++x)
//		{
//			tileSet->SetTileTexture(y, x, currentType);
//		}
//	}
//
//	NewSpriteGo("tilemapSheet", "graphics/Tile/Tilemap_Sheet.png");
//	sprites["tilemapSheet"]->SetPosition({ 50,50 });
//	sprites["tilemapSheet"]->sortLayer = 1;
//
//	for (int i = 0; i < 9; ++i) {
//		typeselectBox[i].setSize({ 32,32 });
//		typeselectBox[i].setPosition(50.f, 50.f + 32.f * i);
//	}
//
//	selectBox.setSize({ 32,32 });
//	selectBox.setPosition(50.f, 50.f);
//	selectBox.setFillColor(sf::Color::Transparent);
//	selectBox.setOutlineThickness(2.f);
//	selectBox.setOutlineColor(sf::Color::White);
//
//	//NewSpriteGo("currentSelectedBox", "graphics/Tile/Tilemap_Sheet.png");
//	//sprites["currentSelectedBox"]->SetPosition({ 50,50 });
//	//sprites["currentSelectedBox"]->sortLayer = 1;
//
//	UiInit();
//	ObjectsSort();
//
//}
//
//void TileEditor::Update(float dt)
//{
//	GameObject :: Update(dt);
//
//
//	screenPos = SCENE_MGR.GetCurrentScene()->UiToScreen((sf::Vector2f)mouse->GetPosition());
//	worldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(screenPos);
//
//	//std::cout << worldPos.x << " " << worldPos.y << std::endl;
//
//	isMouseOutsideAllBoxes = true;
//
//	for (int i = 0; i < 9; ++i) {
//		if (typeselectBox[i].getGlobalBounds().contains(mouse->GetPosition()))
//		{
//			isMouseOutsideAllBoxes = false;
//			if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
//			{
//				selectBox.setPosition(typeselectBox[i].getPosition());
//				currentType = (TileSet::TileType)i;
//			}
//		}
//	}
//	sprites["currentSelectedBox"]->GetSprite()->setTextureRect({ 0,0,32,32 * (int)currentType });
//
//	if (isMouseOutsideAllBoxes)
//	{
//		if (InputMgr::GetMouseButton(sf::Mouse::Left))
//		{
//			tileSet->SetTileTexture(screenPos.x / 32, screenPos.y / 32, currentType);
//		}
//	}
//
//	//std::cout << isMouseOutsideAllBoxes << std::endl;
//}

void TileEditor::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	//for (size_t y = 0; y < tilesInit.size(); ++y)
	//{
	//	for (size_t x = 0; x < tilesInit[y].size(); ++x)
	//	{
	//		tileSet->Draw(window,x,y);
	//	}
	//}
	UiDraw(window);
	window.draw(selectBox);
}

void TileEditor::typeTextSet()
{

}

void TileEditor::typeTextDelete()
{
}
