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
		return L"第一舰队";
	if (troopId == 1)
		return L"第二舰队";
	if (troopId == 2)
		return L"第三舰队";
	return L"第四舰队";
}

void Troop::AddShip(Warship * ship, int index)
{
	if (index >= 0 && index < MAX_TROOP_MEMBER)
	{
		member[index] = ship;
	}
}
