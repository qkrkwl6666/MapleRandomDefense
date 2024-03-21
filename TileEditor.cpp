#include "pch.h"
#include "TileEditor.h"
#include "SpriteGo.h"
#include "Crosshair.h"
#include <Windows.h>
#include <commdlg.h> 
#include "rapidjson/document.h"

using namespace rapidjson;

TileEditor::TileEditor(const std::string& name) : GameObject(name), font(RES_MGR_FONT.Get("fonts/NotoSansKR-Regular.otf"))
{}


void TileEditor::Init()
{

	//tilemapSheet = new SpriteGo("tilemapSheet");
	//tilemapSheet->SetTexture("graphics/Tile/Tilemap_Sheet.png");
	//tilemapSheet->SetPosition({ 50,50 });
	//AddGo(tilemapSheet, Layers::Ui);
}

void TileEditor::Release()
{
}

void TileEditor::Reset()
{
}

void TileEditor::Update(float dt)
{
}

void TileEditor::LateUpdate(float dt)
{
}

void TileEditor::SetCheck(bool c)
{
}

void TileEditor::Draw(sf::RenderWindow& window)
{
}

void TileEditor::HandleMouseSelection()
{
}

void TileEditor::TileMouseSelection(bool isRemove)
{
}

void TileEditor::TileTypeMouseSelection()
{
}

void TileEditor::TileSetTexture(const std::string& filePath)
{
}

void TileEditor::typeTextSet()
{
}

void TileEditor::typeTextDelete()
{
}

std::wstring TileEditor::OpenFile(const wchar_t* filter, HWND owner)
{
	return std::wstring();
}

void TileEditor::SetActiveTypeUI(bool active)
{
}

std::string TileEditor::convertToRelativePath(const std::wstring& absolutePathW)
{
	return std::string();
}
