#pragma once
#include "ComponentDynamic.h"
class BattleItem : ComponentDynamic
{
public:
	BattleItem(wstring imgName, int x, int y, int force, bool shared = false);
	~BattleItem();
	bool shared;
	int force;//0 - �ҷ���1 - �з���2 - ����
};

