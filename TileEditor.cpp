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