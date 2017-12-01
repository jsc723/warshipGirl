#include "stdafx.h"
#include "BattleWarship.h"


BattleWarship::BattleWarship(wstring imgName, int x, int y, int force, Warship *w, int index):
	BattleItem(imgName,x, y, force),
	ComponentWithPicture(imgName, w, x, y, 0.5f, 0),
	index(index)
{
}


BattleWarship::~BattleWarship()
{
}

void BattleWarship::attack(BattleWarship * enemy)
{
	enemy->getDamage(warship->base->huoli + warship->plusHuoli);
}

void BattleWarship::getDamage(int damage)
{
	damage -= warship->base->zhuangjia + warship->plusZhuangjia;
	if (damage < 1)
		damage = 1;
	warship->hp -= damage;
	if (warship->hp <= 0) {
		warship->hp = 0;
	}
}

BattleWarship::BWStatus BattleWarship::status()
{
	if (warship->hp >= warship->base->maxHp / 2) {
		return BWStatus::Good;
	}
	else if (warship->hp > 0) {
		return BWStatus::Broken;
	}
	return BWStatus::Retreated;
}

