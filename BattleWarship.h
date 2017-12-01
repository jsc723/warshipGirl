#pragma once
#include "BattleItem.h"
class BattleWarship :
	public BattleItem, public ComponentWithPicture
{
public:
	enum class BWDirection{North, East, South, West};
	enum class BWStatus{Good, Broken, Retreated};
	BattleWarship(wstring imgName, int x, int y, int force, Warship *w, int index);
	~BattleWarship();
	void attack(BattleWarship * enemy);
	void getDamage(int damage);
	BWStatus status();
	int index;//0 - 5
};

