#include "stdafx.h"
#include "BattleWarship.h"


BattleWarship::BattleWarship(Warship *w, wstring imgName, int x, int y):
	BattleItem(imgName, x, y, 0),
	w(w)
{
}


BattleWarship::~BattleWarship()
{
}

void BattleWarship::attack(BattleWarship * enemy)
{
	enemy->getDamage(w->base->huoli + w->plusHuoli);
}

void BattleWarship::getDamage(int damage)
{
	damage -= w->base->zhuangjia + w->plusZhuangjia;
	if (damage < 1)
		damage = 1;
	w->hp -= damage;
	if (w->hp == 0)
		retreat();
}

void BattleWarship::retreat()
{
	//TODO
}
