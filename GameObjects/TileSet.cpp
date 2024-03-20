#include "pch.h"
#include "TileSet.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" // JSON 문자열화를 위함
#include "rapidjson/filewritestream.h" // 파일 스트림
#include "SpriteGo.h"
#include <cstdio> // C 표준 입출력 관련 함수
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <commdlg.h> // 공통 대화 상자 함수를 위한 헤더

void TileSet::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	for (const auto& row : tiles)
	{
		for (const auto& tile : row)
		{
			window.draw(tile.shape); // 각 타일의 shape를 그린다.
		}
	}
}

void TileSet::SetTileTexture(int y, int x, const TileType& type)
{
	tiles[y][x].texture.loadFromFile("graphics/Tile/Tilemap_Sheet.png");
	tiles[y][x].shape.setTexture(&tiles[y][x].texture);
	tiles[y][x].shape.setTextureRect({ 0,0,32, 32 * (int)type });
	tiles[y][x].shape.setFillColor(sf::Color::White);
	tiles[y][x].shape.setOutlineThickness(0.6f);
	tiles[y][x].type = type;
}

void TileSet::SaveTileMap(const std::string& filePath)
{
	using namespace rapidjson;

	rapidjson::Document doc;
	doc.SetObject();
	Document::AllocatorType& allocator = doc.GetAllocator();

	Value tilesArray(kArrayType);
	for (const auto& row : tiles)
	{
		for (const auto& tile : row)
		{
			Value tileObject(kObjectType);
			tileObject.AddMember("type", (int)tile.type, allocator);
			tileObject.AddMember("x Pos", tile.shape.getPosition().x, allocator);
			tileObject.AddMember("y Pos", tile.shape.getPosition().y, allocator);

			tilesArray.PushBack(tileObject, allocator);
		}
	}
	doc.AddMember("tiles", tilesArray, allocator);

	std::wstring savePath = Utils::OpenSaveFileDialog();
	if (savePath.empty())
	{
		return; // 취소할 경우 return
	}

	std::string sSavePath = Utils::WSTRINGToString(savePath);
	FILE* fp = fopen(sSavePath.c_str(), "wb");

	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	PrettyWriter<FileWriteStream> writer(os);
	doc.Accept(writer);
	fclose(fp);
}

void TileSet::LoadTileMap(const std::string& filePath, const float setOutlineThickness)
{
}
