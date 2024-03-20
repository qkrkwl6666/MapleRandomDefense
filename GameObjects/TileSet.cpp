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
