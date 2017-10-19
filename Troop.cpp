#include "stdafx.h"
#include "Troop.h"


Troop::Troop()
{
	for (int i = 0; i < 6; i++) {
		member[i] = NULL;
	}
}


Troop::~Troop()
{

}

LPCWSTR Troop::getName()
{
	if (troopId == 0)
		return L"��һ����";
	if (troopId == 1)
		return L"�ڶ�����";
	if (troopId == 2)
		return L"��������";
	return L"���Ľ���";
}

void Troop::AddShip(Warship * ship, int index)
{
	if (index >= 0 && index < MAX_TROOP_MEMBER)
	{
		member[index] = ship;
	}
}
