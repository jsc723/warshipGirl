#include "stdafx.h"
#include "BattleMap.h"
#include <algorithm>


BattleMap::BattleMap()
{
	
}


BattleMap::~BattleMap()
{
}

void BattleMap::put(BattleItem * b, int x, int y)
{
	if (!getUnique(x, y)) {
		delete b;
		return;
	}
	map[x][y].push_back(b);
}

void BattleMap::moveUnique(int x0,int y0, int x1, int y1)
{
	auto &block = map[x0][y0];
	auto it = std::find_if(block.begin(), block.end()
		, [](BattleItem *b) {return b->shared == false; });
	if (it == block.end())
		return;
	block.erase(it);
	put(*it, x1, y1);
}

BattleItem * BattleMap::getUnique(int x, int y)
{
	auto &block = map[x][y];
	auto it = std::find_if(block.begin(), block.end()
		, [](BattleItem *b) {return b->shared == false; });
	return it == block.end() ? nullptr : *it;
}
