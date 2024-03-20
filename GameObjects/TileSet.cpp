#include "pch.h"
#include "TileSet.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h" // JSON ���ڿ�ȭ�� ����
#include "rapidjson/filewritestream.h" // ���� ��Ʈ��
#include "SpriteGo.h"
#include <cstdio> // C ǥ�� ����� ���� �Լ�
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <commdlg.h> // ���� ��ȭ ���� �Լ��� ���� ���
#pragma warning(disable : 4996)

void TileSet::Draw(sf::RenderWindow& window, int x, int y)
{
	GameObject::Draw(window);
	window.draw(tiles[y][x].shape);
}


void TileSet::LoadTileTexture(const std::string& FilePath)
{
	tileTexture.loadFromFile(FilePath);
}

void TileSet::SetTileTexture(int y, int x, const TileType& type)
{
	tiles[y][x].shape.setTexture(&tileTexture);
	tiles[y][x].shape.setTextureRect({ 0, 32*(int)type,32, 32 });
	tiles[y][x].shape.setSize({ 32.f ,32.f });
	tiles[y][x].shape.setPosition({ y * 32.f , x * 32.f });
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
		return; // ����� ��� return
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
