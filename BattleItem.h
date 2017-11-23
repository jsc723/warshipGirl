#pragma once
#include "ComponentDynamic.h"
class BattleItem : public ComponentDynamic
{
public:
	BattleItem(wstring imgName, int x, int y, LPARAM lp);
	~BattleItem();
	bool shared = false;
	int force;//0 - 我方，1 - 敌方，2 - 其他
};

