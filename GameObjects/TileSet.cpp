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
	window.draw(tiles[y][x].va);
}


void TileSet::LoadTileTexture(const std::string& FilePath)
{
	tileTexture.loadFromFile(FilePath);
}
