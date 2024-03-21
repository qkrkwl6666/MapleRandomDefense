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

TileSet::TileSet()
{
}

void TileSet::Init()
{
	tiles = std::vector<std::vector<Tile>>{ 256, std::vector<Tile>(256) }; // Ÿ��Ÿ�� �����ϴ� �迭
	VaSet();
}

void TileSet::VaSet()
{
	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(4 * 256 * 256);

	sf::Vector2f posOffsets[4] = {
		{ 0, 0 },
		{ 32, 0 },
		{ 32 , 32 },
		{ 0 , 32 },
	};

	for (int i = 0; i < tiles.size(); i++)
	{

		for (int j = 0; j < 256; j++)
		{
			int quadIndex = i * 256 + j;
			sf::Vector2f quadPos(32 * j, 32 * i);
			int type = (int)tiles[j][i].type;
			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = (quadIndex * 4) + k;
				va[vertexIndex].position = quadPos + posOffsets[k];
				va[vertexIndex].texCoords = posOffsets[k];
				va[vertexIndex].texCoords.y += type * 32.f;
			}
		}
	}
}

void TileSet::SetTileType(int x, int y, TileType type)
{
	tiles[x][y].type = type;
	VaSet();
}

void TileSet::Update(float dt)
{
	GameObject::Update(dt);
}

void TileSet::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = &RES_MGR_TEXTURE.Get("graphics/Tile/Tilemap_Sheet.png");
	window.draw(va, state);
}

void TileSet::SaveTileMap(const std::string& filePath)
{
	using namespace rapidjson;

	rapidjson::Document doc;
	doc.SetObject();
	Document::AllocatorType& allocator = doc.GetAllocator(); // �޸� �Ҵ��� ȹ��
	Value tilesArray(kArrayType);

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < 256; j++)
		{
			int quadIndex = i * 256 + j;
			sf::Vector2f quadPos(32 * j, 32 * i);
			Value tileObject(kObjectType); // ���� Ÿ�� ������ ���� JSON ��ü ����
			tileObject.AddMember("type", (int)tiles[j][i].type, allocator); // Ÿ�� Ÿ�� ���� �߰�
			tileObject.AddMember("x Pos", quadPos.x, allocator);
			tileObject.AddMember("y Pos", quadPos.y, allocator);

			// Ÿ�� ��ü�� Ÿ�� �迭�� �߰�
			tilesArray.PushBack(tileObject, allocator);
		}
	}


	// Ÿ�� �迭�� ����
	doc.AddMember("tiles", tilesArray, allocator);
	std::ofstream file(filePath);
	if (file.is_open()) {
		StringBuffer buffer;
		PrettyWriter<StringBuffer> writer(buffer);
		doc.Accept(writer);
		file << buffer.GetString();
		file.close();
	}
	// ���� ������ �����ؾ���



	std::wstring savePath = Utils::OpenSaveFileDialogToJson();
	if (savePath.empty())
	{
		return; // ����� ��� return
	}

	// JSON ������ ���Ͽ� ����
	// TODO : fopen �����ϱ�
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
	std::ifstream file(filePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string contents = buffer.str();

	rapidjson::Document doc;
	if (doc.Parse(contents.c_str()).HasParseError())
	{
		return; // �Ľ� ���� ó��
	}

	const rapidjson::Value& tilesArray = doc["tiles"];
	tiles.resize(256, std::vector<Tile>(256));

	SetCurrentDirectory(currentDirectory);

	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < 256; j++)
		{
			const rapidjson::Value& tileObject = tilesArray[i * 256 + j];
			TileType type = static_cast<TileType>(tileObject["type"].GetInt());
			tiles[j][i].type = type;
		}
	}
}
