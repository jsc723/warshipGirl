#pragma once
#include "BattleItem.h"
class BattleWarship :
	public BattleItem
{
public:
	enum class BWDirection{North, East, South, West};
	BattleWarship(Warship *w, wstring imgName, int x, int y);
	~BattleWarship();
	void attack(BattleWarship * enemy);
	void getDamage(int damage);
	void retreat();
	Warship *w;
	int index;//0 - 5
};

