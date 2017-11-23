#include "stdafx.h"
#include "BattleMap.h"


BattleMap::BattleMap()
{
}


BattleMap::~BattleMap()
{
}

void BattleMap::moveUnique(int x0, int y0, int x1, int y1)
{
	auto block = map[x0][y0];
	for (auto it = block.begin(); it != block.end(); it++) {
		BattleItem *b = *it;
		if (b->shared == false) {
			block.erase(it);
			map[x1][y1].push_back(b);
			return;
		}
	}
}
