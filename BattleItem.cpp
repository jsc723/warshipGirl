#include "stdafx.h"
#include "BattleItem.h"


BattleItem::BattleItem(wstring imgName, int x, int y, int force, bool shared) :
	ComponentDynamic(imgName, x, y, 0)
{
}


BattleItem::~BattleItem()
{
}
