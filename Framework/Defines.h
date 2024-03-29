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
	WALL, // ������ ��
	WATER, // ��
	SNOW,// ��ġ ������ ��
	GRASS, // �� ���� ��ȸ����
	SPACE, //����Ұ����� �ݸ�����
	ENEMYSPAWN, // �� ���� ��������
	TOWERSPAWN, // Ÿ�� ��������
	SELECTOFF, // ���� ��� ����
	SELECTON, // ���� ���� (���� ����)
};