#include "stdafx.h"
#include "BattleItem.h"


BattleItem::BattleItem(wstring imgName, int x, int y, LPARAM lp) :
	ComponentDynamic(imgName, x, y, lp)
{
}


BattleItem::~BattleItem()
{
}
