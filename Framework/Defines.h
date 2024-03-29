#pragma once

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR, ML, MC, MR, BL, BC, BR, Custom,
};

enum class Sides
{
	None = -1, Left, Right, Count
};

enum class Languages
{
	Korean,
	English,
};

enum class TileType
{
	WALL, // 막히는 벽
	WATER, // 물
	SNOW,// 배치 가능한 땅
	GRASS, // 적 유닛 순회구역
	SPACE, //통과불가능한 격리구역
	ENEMYSPAWN, // 적 유닛 스폰구역
	TOWERSPAWN, // 타워 스폰구역
	SELECTOFF, // 선택 대기 구역
	SELECTON, // 선택 구역 (들어가면 선택)
};