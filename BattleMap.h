#pragma once
#include <vector>
#include "BattleItem.h"
class BattleMap
{
public:
	BattleMap();
	~BattleMap();
	static const int MAP_SIZE = 8;
	void put(BattleItem *b, int x, int y);
	void moveUnique(int x0, int y0, int x1, int y1);
	BattleItem *getUnique(int x, int y);
private:
	vector<BattleItem *> map[MAP_SIZE][MAP_SIZE];
};

